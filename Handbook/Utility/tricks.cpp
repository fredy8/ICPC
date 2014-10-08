//tokenize a string
char str[100] = "jkans asjna asjnxa asmx", del[2] = " ";
for(char *tk = strtok(str, del); tk; tk = strtok(0, del))
	cout << tk << endl;

Bipartite graphs:
MVC = MCBM
MIS = V - MCBM

printf("%ld\n", strtol("222", 0, x)); //base x to long