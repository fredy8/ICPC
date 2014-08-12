typedef long long ll;
ll mod(ll a, ll b) {
  return ((a%b)+b)%b;
}

ll modpow(ll base, ll exp, ll modulus) {
    base = mod(base, modulus);
    ll result = 1;
    while (exp) {
        if (exp & 1) result = mod(result * base, modulus);
        base = mod(base * base, modulus);
        exp >>= 1;
    }
    return result;
}