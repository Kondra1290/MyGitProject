if [ -n "$1" ]; then
    delay=$1
else
    delay=0.1 
fi

input=$(cat)

lines=$(echo "$input" | wc -l)
max_width=$(echo "$input" | awk '{ print length }' | sort -n | tail -n 1)

terminal_height=$(stty size < /dev/tty | cut -d' ' -f1)
terminal_width=$(stty size < /dev/tty | cut -d' ' -f2)

offset_x=$(( (terminal_width - max_width - 2) / 2 ))
offset_y=$(( (terminal_height - lines - 2) / 2 ))

clear
tput civis

for (( i=0; i<max_width+2; i++ )); do
    tput cup $offset_y $((offset_x + i))
    echo -n "─"
done

for (( i=0; i<lines; i++ )); do
    tput cup $((offset_y + i + 1)) $offset_x
    echo -n "│"
    tput cup $((offset_y + i + 1)) $((offset_x + max_width + 1))
    echo -n "│"
done

for (( i=0; i<max_width+2; i++ )); do
    tput cup $((offset_y + lines + 1)) $((offset_x + i))
    echo -n "─"
done

positions=$(echo "$input" | awk '{
    for (i = 1; i <= length($0); i++) {
        print i-1 " " NR-1 " " substr($0, i, 1)
    }
}' | shuf)

random_color() {
    echo $((31 + RANDOM % 7))
}

echo "$positions" | while read col row char; do
    color=$(random_color) 

    tput setaf $color
    tput cup $((offset_y + row + 1)) $((offset_x + col + 1)) 
    echo -n "$char"
    
    sleep "$delay"
done

tput cnorm
tput cup $((terminal_height - 1)) 0

