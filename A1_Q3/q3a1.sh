#!/bin/bash

#1-----------------------------------------
if [ ! -f "input.txt" ]; then
    echo "Error: File not found"
    exit 1
fi

#2-----------------------------------------
mkdir -p Result

#3-----------------------------------------
while IFS= read -r line || [ -n "$line" ]; do
    #3.1-----------------------------------
    [ -z "$line" ] && continue

    #3.2-----------------------------------
    read -a array <<< "$line"
    
    #3.3-----------------------------------
    if [ ${#array[@]} -ne 3 ]; then
        echo "Error: Invalid input format - ${line}"
        continue
    fi
    
    x=${array[0]}
    y=${array[1]}
    operation=${array[2]}
    
    #4--------------------------------------
    case $operation in
        "xor")
            result=$((x ^ y))
            ;;
        "product")
            result=$((x * y))
            ;;
        "compare")
            if [ $x -gt $y ]; then
                result=$x
            else
                result=$y
            fi
            ;;
        *)
            echo "Error: Invalid operation - ${operation}"
            continue
            ;;
    esac
    
    #5-----------------------------------------
    echo $result >> Result/output.txt
    
done < input.txt

echo "Calculated: Results stored in Result >> output.txt"
