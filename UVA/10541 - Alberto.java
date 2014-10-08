import java.util.Scanner;
import java.math.BigInteger;;

public class Main {
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		int casos = scanner.nextInt();
		while (casos-- > 0) {
			int N, K, S = 0;
			K = scanner.nextInt();
			N = scanner.nextInt();
			for (int i = 0; i < N; i++) {
				S += scanner.nextInt();
			}
			System.out.println(nCr(K-S+1, N));
		}
		scanner.close();
	}
	
	public static BigInteger nCr (int n, int r) {
		if (n < r) return BigInteger.ZERO;
		BigInteger t = BigInteger.ONE;
		if (n == r || r == 0) return t;
		for (int i = 0; i < r; i++) {
			t = t.multiply(BigInteger.valueOf(n-i));
		}
		for (int i = 1; i <= r; i++) {
			t = t.divide(BigInteger.valueOf(i));
		}
		return t;
	}
}