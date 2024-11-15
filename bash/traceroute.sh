#!/bin/bash
# Скрипт отримує URL як параметр
URL=$1

# Виконуємо traceroute
echo "Running traceroute for $URL"
traceroute -n $URL | awk '{if (NR>1 && $2 != "*") print $2}'
