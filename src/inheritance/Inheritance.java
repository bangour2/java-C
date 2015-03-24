package inheritance;

class A { 
	final void meth() { 
		System.out.println("This is a final method."); } 
	
	int x1;
     A(int x){
    	 this.x1 = x;}}
class B extends A { 
	//void meth() { // ERROR! Can't override. 
	 
	 int z1;
	 B(int x, int z){
		 super(x);
		 this.z1 = z;}
}
public class Inheritance{
	 public static void main(String args[])
     {
		 B output = new B(1,5);
		 System.out.println(output.x1);
     }
}

