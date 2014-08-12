// x[i] = f(x[i-1])
ii floydCycleFinding(int x0) {
	int tortoise = f(x0), hare = f(f(x0));  //Encontrar el primer xi = x2i
	while (tortoise != hare) { tortoise = f(tortoise); hare = f(f(hare)); }
	int mu = 0; hare = x0;   //Encontrar mu usando el rango i
	while (tortoise != hare) { tortoise = f(tortoise); hare = f(hare); mu++; }
	int lambda = 1; hare = f(tortoise);   //Encontrar lambda teniendo mu
	while (tortoise != hare) { hare = f(hare); lambda++; }
	return ii(mu, lambda);
}