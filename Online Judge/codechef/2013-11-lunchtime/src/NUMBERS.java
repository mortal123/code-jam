
import java.util.*;
import java.lang.*;

public class NUMBERS {
	public static void main(String args[]) {
		Scanner input = new Scanner(System.in);
		int testCount = input.nextInt();
		for(; testCount-- > 0; ) {
			int n = input.nextInt();
			Data[] list = new Data[n];
			for(int i = 0; i < n; i++) {
				String name = input.next();
				int x = input.nextInt();
				list[i] = new Data(x, name);
			}
			Arrays.sort(list);
			//for(int i = 0; i < n; i++) {
			//	System.out.println(list[i].number + list[i].name);
			//}
			for(int i = 0; i < n; ) {
				if (i + 1 >= n || list[i + 1].number != list[i].number) {
					System.out.println(list[i].name);
					break;
				} else {
					for(int tmp = list[i].number ; i < n && list[i].number == tmp; i++);
					if (i == n) {
						System.out.println("Nobody wins.");
					}
				}
			}
		}
		input.close();
	}
}

class Data implements Comparable { 
	int number;
	String name;
	Data(int x, String str) {
		this.number = x;
		this.name = str;
	}
	public int compareTo(Object o) {
		return this.number - ((Data)o).number;
	}
}


