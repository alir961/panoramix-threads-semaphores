#!/usr/bin/env bash
# Runs panoramix over many parameter combinations and checks the simulation's invariants.
# Usage: tests/stress.sh ./panoramix   (build with -fsanitize=thread to also catch data races)
set -uo pipefail

BIN=${1:-./panoramix}
TIMEOUT=${TIMEOUT:-20}
export PANORAMIX_FIGHT_MS=${PANORAMIX_FIGHT_MS:-0}
runs=0; failures=0

fail() { echo "FAIL [$*]"; failures=$((failures + 1)); }

check() {
    local v=$1 pot=$2 fights=$3 refills=$4 out status
    out=$(timeout "$TIMEOUT" "$BIN" "$v" "$pot" "$fights" "$refills" 2>&1); status=$?
    runs=$((runs + 1))
    local args="$v $pot $fights $refills"

    [ $status -eq 124 ] && { fail "$args: deadlock (timed out)"; return; }
    [ $status -ne 0 ] && { fail "$args: exit $status"; return; }
    grep -q 'ThreadSanitizer\|AddressSanitizer' <<<"$out" && { fail "$args: sanitizer report"; echo "$out" | head -20; return; }

    # Every serving is drunk: total fights = min(villagers * fights, pot * (refills + 1))
    local expected=$(( v * fights < pot * (refills + 1) ? v * fights : pot * (refills + 1) ))
    local attacks; attacks=$(grep -c 'Take that roman scum' <<<"$out")
    [ "$attacks" -ne "$expected" ] && fail "$args: $attacks fights, expected $expected"

    local made; made=$(grep -c 'Ah! Yes, yes' <<<"$out")
    [ "$made" -gt "$refills" ] && fail "$args: $made refills, only $refills allowed"

    for ((id = 0; id < v; id++)); do
        local n; n=$(grep -c "^Villager $id: Take that" <<<"$out")
        [ "$n" -gt "$fights" ] && fail "$args: villager $id fought $n times"
        grep -q "^Villager $id: I'm going to sleep now." <<<"$out" || fail "$args: villager $id never went to sleep"
    done
    grep -q "^Druid: I'm out of viscum. I'm going back to... zZz" <<<"$out" || fail "$args: druid never went back to sleep"
}

for v in 1 2 3 5 8; do
    for pot in 1 2 5; do
        for fights in 1 3; do
            for refills in 1 2 4; do
                check "$v" "$pot" "$fights" "$refills"
            done
        done
    done
done

# Invalid arguments must exit with 84
for bad in "" "1 2 3" "0 1 1 1" "1 0 1 1" "-2 1 1 1" "a b c d"; do
    runs=$((runs + 1))
    # shellcheck disable=SC2086
    timeout 5 "$BIN" $bad >/dev/null 2>&1; s=$?
    [ $s -ne 84 ] && fail "args '$bad': exit $s, expected 84"
done

echo "$runs runs, $failures failures"
[ $failures -eq 0 ]
