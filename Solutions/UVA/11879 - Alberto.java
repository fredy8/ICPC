import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		BigInteger n = scanner.nextBigInteger(), d = BigInteger.valueOf(17);
		while (!n.equals(BigInteger.ZERO)) {
			if (n.remainder(d).equals(BigInteger.ZERO)) {
				System.out.println(1);
			} else {
				System.out.println(0);
			}
			n = scanner.nextBigInteger();
		}
		scanner.close();
	}
}