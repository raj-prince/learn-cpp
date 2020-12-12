#!/usr/bin/env bash

# Please set the CCODING_HOME in the .bash_profile
# Command: ccoding [command_type] [argument]

COMMAND_TYPE=("create" "append" "compile" "run")

function Create() {
    echo "Create File: ${1}"
    touch $1
    file_name="${CCODING_HOME}/algorithm/template.cpp"
    echo $file_name
    cat $file_name >> $1
    xed $1
}

function Append() {
    file_to_append="${CCODING_HOME}/algorithm/${1}.cpp"
    file_into_append=$2;
    echo "Append content of ${file_to_append} into ${file_into_append}"
    echo "// Appending Code for: ${1}" >> $file_into_append
    cat $file_to_append >> $file_into_append
}

function Compile() {
    echo "Compiling file: ${1}"
    g++ -std=c++17 "${1}" -o "${1}.out"
}

function Run() {
    echo "Running file: ${1}"
    "./${1}.out"
}

if [[ ! " ${COMMAND_TYPE[@]} " =~ " ${1} " ]]; then
    echo "Not a valid command!!!"
    exit 0
fi

case "$1" in
    "create") Create $2 ;;
      
    "append") Append $2 $3 ;;
      
    "compile") Compile $2 ;;
    
    "run") Run $2 ;;
esac


