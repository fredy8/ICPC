/* Sieve of Atkin
Obtains primes in the range [1, n]
*/
typedef vector<ll> vll;
vll primes;
void sieve_atkins(ll n) {
   vector<bool> isPrime(n + 1);
   isPrime[2] = isPrime[3] = true;
   for (ll i = 5; i <= n; i++)
      isPrime[i] = false;

   ll lim = ceil(sqrt(n));
   for (ll x = 1; x <= lim; x++) {
      for (ll y = 1; y <= lim; y++) {
         ll num = (4 * x * x + y * y);
         if (num <= n && (num % 12 == 1 || num % 12 == 5))
            isPrime[num] = true;
         num = (3 * x * x + y * y);
         if (num <= n && (num % 12 == 7))
            isPrime[num] = true;
         if (x > y) {
            num = (3 * x * x - y * y);
            if (num <= n && (num % 12 == 11))
               isPrime[num] = true;
         }
      }
   }

   for (ll i = 5; i <= lim; i++)
      if (isPrime[i])
         for (ll j = i * i; j <= n; j += i)
            isPrime[j] = false;

   for (ll i = 2; i <= n; i++)
      if (isPrime[i])
         primes.pb(i);
}
