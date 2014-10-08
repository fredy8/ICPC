import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		int casos = scanner.nextInt();
		while (casos-- > 0) {
			BigInteger a, b, g;
			String c;
			a = scanner.nextBigInteger();
			c = scanner.next();
			b = scanner.nextBigInteger();
			g = a.gcd(b);
			System.out.println(a.divide(g).toString() + " / " + b.divide(g).toString());
		}
		scanner.close();
	}		
}