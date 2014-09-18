import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		int n, x;
		while (scanner.hasNextInt()) {
			n = scanner.nextInt();
			x = scanner.nextInt();
			if (x == 1) System.out.println(n*(n+1)/2);
			else System.out.println(funcion(n, x));
		}
		scanner.close();
	}

	public static BigInteger funcion(int n, int x) {
		BigInteger R, N, X, pot, uno;
		N = BigInteger.valueOf(n);
		X = BigInteger.valueOf(x);
		pot = X.pow(n);
		uno = BigInteger.ONE;
		R = X.multiply((N.multiply(X.multiply(pot))).subtract(N.add(uno).multiply(pot)).add(uno)).divide((X.subtract(uno)).pow(2));
		return R;
	}
	
}