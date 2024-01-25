#!/bin/bash
#
# Copyright (C) 2023 Avidsen - All Rights Reserved
#
# You should have received a copy of the license with
# this file. If not, please write to: contact-rd@avidsen.com

HISTORY="${XDG_CACHE_HOME:-$HOME/.cache}/ao-history"
HTTPIE_DISPLAY="${AO_MORIA_DISPLAY:-b}"
SESSION=
SERVER=$1

function call_httpie {
    http --print=$HTTPIE_DISPLAY --session="$SESSION" "$@"
}

function die {
    echo "$1"
    exit 1
}

function do_http_request {
    local method uri

    if [ -n "$SESSION" ]; then
        method=$2
        uri="$SERVER$1$3"
        shift 3
        call_httpie "$method" "$uri" "$@"
    else
        echo "No Session"
    fi
}

function handle_dain_commands {
    local cmd

    cmd=$(echo "$1" | tr "[:upper:]" "[:lower:]")
    case "$cmd" in
        "login")
            handle_new_session "$2" "$3"
            ;;
        "delete" | "get" | "post" | "put")
            do_http_request "/services/dain" "$@"
            ;;
        *)
            echo "Unknown Dain command $cmd"
    esac
}

function handle_dis_commands {
    local cmd

    cmd=$(echo "$1" | tr "[:upper:]" "[:lower:]")
    case "$cmd" in
        "delete" | "get" | "post" | "put")
            do_http_request "/services/dis" "$@"
            ;;
        *)
            echo "Unknown Dis command $cmd"
    esac
}

function handle_durin_commands {
    local cmd

    cmd=$(echo "$1" | tr "[:upper:]" "[:lower:]")
    case "$cmd" in
        "delete" | "get" | "post" | "put")
            do_http_request "/services/durin" "$@"
            ;;

        # TODO Implement sift URL filter1=value1 [filter2=...]
        # TODO Implement page (prev|next|n) to navigate in collections
        *)
            echo "Unknown Durin command $cmd"
    esac
}

function on_exit {
    # Save the current history session.
    history -w "$HISTORY"
    echo -e "\nHistory saved"
}

function handle_new_session {
    local body error token

    # Delete any previous httpie session.
    rm -rf "$HOME/.httpie/sessions/$SESSION"

    # Proceed to authentication and extract the token.
    body=$(curl -s -X POST "$SERVER/services/dain/login" \
        -H "Content-Type: application/json" \
        -d '{"login": "'"$1"'", "password": "'"$2"'"}')
    error=$(echo "$body" | jq '.error.status')

    if [ "null" = "$error" ]; then
        token=$(echo "$body" | jq '.token' | tr '"' ' ')
        SESSION=$(session_name "$1")

        # Proceed to a simple request to store the token in the session.
        call_httpie GET "$SERVER/services/dain/login" Authorization:"Bearer $token"
    else
        echo -e "Error $error $(echo $body | jq .error.reason) on login"
    fi
}

function prompt {
    local context=$1

    echo -e "\e[1;33m${SESSION#*__}\e[0m[\e[1m${SERVER#*//}\e[0m] \e[1;35m$context\e[0m > "
}

function session_name {
    local login=$1 prefix

    if [[ "$SERVER" == http* ]]; then
        prefix=$(echo "$SERVER" | cut -d'/' -f 3)
    else
        prefix=$(echo "$SERVER" | cut -d':' -f 1)
    fi

    echo "$prefix"__"$(echo "$login" | cut -d@ -f 1)"
}


[ $# -eq 1 ] || die "Usage: $0 <server>"

# The initial context depends on the way the script is called.
context=$(basename "$0" .sh)

# Load the history file
history -r "$HISTORY"

trap on_exit EXIT

while true; do
    read -r -p "$(prompt "$context")" -e line

    cmd=${line%% *}

    history | grep -q "$line"
    [ $? == 1 ] && history -s "$line";

    case "$cmd" in
        "dain" | "dis" | "durin")
            if [ "$cmd" == "$line" ]; then
                context=$cmd;
            else
                eval handle_"$cmd"_commands "${line#* }"
            fi
            ;;
        "hclear")
            history -c;
            ;;
        *)
            eval handle_"$context"_commands "$line"
    esac
done
