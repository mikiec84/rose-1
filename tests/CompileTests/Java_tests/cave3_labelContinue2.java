
public class cave3_labelContinue2 {
	void test() {
		int i = 0;
		int j = 10;
		// breaks in a children of the labeled statement
		// and cfg has to traverse enclosing labeled statements
		l: while (i < j) {
			p: while (i < j) {
				i = i + 1;
				continue p;
			}
		}
		// assert i == 100
	}
}
