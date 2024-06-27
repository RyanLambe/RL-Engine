#! /bin/bash

# clang-format all src files
for path in ./Editor/src/ ./Engine/src/ ./Sandbox/src/; do
    find $path -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i -style=file
done

# lint ???