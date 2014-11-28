import java.io.*;
import java.util.*;
import java.math.*;

public class LEBALONS {
	static int N = 40;
	public static void main(String args[]) {
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		int test = cin.nextInt();
		MathContext mc = new MathContext(25, RoundingMode.HALF_DOWN);
		while((test--) > 0) {
			int[] a = new int[N + 1], b = new int[N + 1];
			for(int i = 0; i <= N; i++) {
				a[i] = 0; 
				b[i] = 0;
			}
			int n = cin.nextInt(), m = cin.nextInt();
			BigDecimal[][] ways = new BigDecimal[N + 1][N + 1], totv = new BigDecimal[N + 1][N + 1];
			for(int i = 1; i <= n; i++) {
				int c = cin.nextInt(), p = cin.nextInt();
				a[c]++;
				b[c] += p;
			}
			for(int i = 0; i <= N; i++)
				for(int j = 0; j <= N; j++) {
					ways[i][j] = BigDecimal.ZERO;
					totv[i][j] = BigDecimal.ZERO;
				}
			ways[0][0] = BigDecimal.ONE;
			for(int i = 0; i < N; i++) {
				BigDecimal p = (BigDecimal.valueOf(2)).pow(a[i + 1], mc);
				for(int j = 0; j <= i; j++) {
					totv[i + 1][j] = totv[i + 1][j].add(totv[i][j]);
					ways[i + 1][j] = ways[i + 1][j].add(ways[i][j]);
					if (a[i + 1] > 0) {
						totv[i + 1][j + 1] = totv[i + 1][j + 1].add(totv[i][j]).add(
								BigDecimal.valueOf(b[i + 1]).multiply(ways[i][j]).multiply(p.divide(BigDecimal.valueOf(2)))
								);
						ways[i + 1][j + 1] = ways[i + 1][j + 1].add(ways[i][j].multiply(p.subtract(BigDecimal.ONE)));
					}
				}
			}
			BigDecimal ta = BigDecimal.valueOf(0), tb = BigDecimal.valueOf(0);
			for(int i = m; i <= N; i++) {
				ta = ta.add(totv[N][i]);
				tb = tb.add(ways[N][i]);
			}
			System.out.printf("%.10f\n", ta.divide(tb, mc));
		}
	}
}
