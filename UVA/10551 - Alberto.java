import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static final BigInteger DOS = new BigInteger("2");
	public static final long MOD = 1000000000;
	public static final long EF = 1562500;
	
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		int b;
		String p, m;
		BigInteger R, P, M;
		while (scanner.hasNext()) {
			b = scanner.nextInt();
			if (b == 0) break;
			p = scanner.next();
			m = scanner.next();
			P = toBase10(p, b);
			M = toBase10(m, b);
			R = P.mod(M);
			System.out.println(Integer.toString(R.intValue(), b));
		}
		scanner.close();
	}
	
	public static BigInteger toBase10(String n, int b) {
		BigInteger res = BigInteger.ZERO, B = BigInteger.valueOf(b);
		for (int i = 0; i < n.length(); i++) {
			res = res.multiply(B);
			res = res.add(BigInteger.valueOf((int)(n.charAt(i) - '0')));
		}
		return res;
	}
	
}