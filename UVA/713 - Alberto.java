import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		while (n-- > 0) {
			BigInteger a, b, c;
			a = scanner.nextBigInteger();
			b = scanner.nextBigInteger();
			c = (new BigInteger(reverse(a.toString()))).add(new BigInteger(reverse(b.toString())));
			System.out.println(new BigInteger(reverse(c.toString())));
		}
		scanner.close();
	}

	public static String reverse(String s) {
		String r = new StringBuilder(s).reverse().toString();
		return r;
	}
	
}