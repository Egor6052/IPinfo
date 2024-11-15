#!/bin/bash

# Отримуємо IP як параметр
IP=$1

# Виконуємо запит до ipinfo.io для отримання інформації про IP
curl -s "https://ipinfo.io/$IP"
