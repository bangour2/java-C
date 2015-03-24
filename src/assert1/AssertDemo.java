package assert1;

public class AssertDemo {
    
	static int val =3;
	static int getnum() { return val--; }
	public static void main(String[] args) {

		int n =-5 ;
		for(int i=0; i < 10; i++) { 
			n = getnum();
			assert n > 0 : "n is negative"; 
			System.out.println("n is " + n);
}
	}}
