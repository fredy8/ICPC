import java.util.Scanner;
import java.math.BigDecimal;

public class Main {
	public static void main(String args[]) {
		Scanner scanner = new Scanner(System.in);
		int casos = scanner.nextInt();
		while (casos-- > 0) {
			BigDecimal n, s = BigDecimal.ZERO;
			while (true) {
				n = scanner.nextBigDecimal();
				if (n.equals(BigDecimal.ZERO)) break;
				s = s.add(n);
			}
			System.out.println(format(s));
		}
		scanner.close();
	}
	
	public static String format(BigDecimal n) {
		String m = n.toString();
		if (!m.contains("."))
			return m;
		int l = m.length()-1;
		while (m.charAt(l) == '0') {
			m = m.substring(0, l--);
		}
		if (m.charAt(l) == '.') {
			m = m.substring(0, l);
		}
		return m;
	}
}