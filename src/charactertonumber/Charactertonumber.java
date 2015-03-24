package charactertonumber;

public class Charactertonumber {
	
	public static String charactertonumber(String name){
		
		int value = 0;
		String output = "";
		
		name = name.replace(" ", "");
		name = name.toUpperCase();
		
		for(int i = 0; i< name.length(); i++){
		value = Math.abs(65 - (int)(name.charAt(i)));	
		output = output + value + " ";}
		
		return output;}

	public static void main(String[] args) {
      System.out.println(charactertonumber("allornothing"));
	}}
