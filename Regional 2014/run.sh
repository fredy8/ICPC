clear;
g++ $1 -op && python -c "import re;print(re.search(r'^/\*\n((?s).*)\*/',open('$1').read()).group(1))" | ./p;
rm p
