#!/usr/bin/env bash

for dir in */ ; do
    if [ -f "$dir/main.cpp" ]; then
        echo "==============================="
        echo "Building $dir"
        echo "==============================="

        g++ -std=c++20 "$dir/main.cpp" \
            -o "$dir/game.exe" \
            -lsfml-graphics \
            -lsfml-window \
            -lsfml-system

        if [ $? -eq 0 ]; then
            echo "✅ Success"
        else
            echo "❌ Failed"
        fi

        echo
    fi
done

echo "All games processed!"