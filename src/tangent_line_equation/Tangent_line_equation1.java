package tangent_line_equation;

import java.math.BigInteger;

public class Tangent_line_equation1 {
	
	static double y1 = 0, x1 =0, y0 =0, x0 =0;
	public static String m_;
	public static String b_;
	
	public static String num_date(int count){
		
		int[] num = {2692312, 46751};
		//, 72335, 865133, 912790, 258223,1067508, 443508, 16034, 136754, 1397825};
		int[] date = {125154, 1225144};
		//1225141, 1125141, 1025141, 925141,825141, 725141, 625141, 525141, 425141};
		return avg(num, date) +"";}
	
	public static String avg(int[] num, int[] date){
		int sum_num = 0, sum_date = 0;		
		for(int i = 0; i< num.length; i+=2){
			sum_num += num[i];
			sum_date += date[i];}
		
		x0 = sum_date/(num.length/2);
		y0 = sum_num/(num.length/2);
		
		sum_num = 0; sum_date = 0;
		for(int i = 1; i< num.length; i+=2){
			sum_num += num[i];
			sum_date += date[i];}
		
		x1 = sum_date/(num.length/2);
		y1 = sum_num/(num.length/2);
		
		return result(y1, x1, y0, x0) +"";	
	}
	
	public static String result(double y1, double x1, double y0, double x0){
		double m = (y1-y0)/(x1-x0);
	    long b = (long) (y0 - (m*x0));
		return m +"x "+ b;}
	
	public static String result2(BigInteger y1, BigInteger x1, BigInteger y0, BigInteger x0){
		BigInteger numerator = y1.subtract(new BigInteger(y0+""));
		BigInteger denominator = x1.subtract(new BigInteger(x0+""));
		BigInteger m = numerator.divide(new BigInteger(denominator+""));
		BigInteger c = m.multiply(new BigInteger(x0+""));
		BigInteger b = y0.subtract(new BigInteger(c+""));
		
		m_ = m+""; b_ = b+"";
		return m +"x "+ b;}

	public static void main(String[] args) {
		  System.out.print(num_date(0));
	      
	}}
