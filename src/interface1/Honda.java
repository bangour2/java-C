package interface1;

public class Honda implements Vehicle, Company, Accord {

	public int accelerate(int x) {
		return x*x;
	}

	public int brake(int x) {
		return x/x;
	}

	public void name() {
        System.out.println("Ford");		
        switch(brake(1)){
    	case NO:
    		System.out.println("NO"); break;
    	case YES:
    		System.out.println("YES"); break;}
	}

	public int cost(int x) {
		// TODO Auto-generated method stub
		return x*x*x;
	}
	

}
