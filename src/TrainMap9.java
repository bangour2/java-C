
public class TrainMap9 {

	public void result(){
	      int one_five = 0;	      
	      String [] hold = {"AB", "BC", "CD", "DC", "DE", "AD", "CE", "EB", "AE"};
	      int[] hold_int = {5,4,8,8,6,5,2,3,7};
	      
	      String[] hold_temp = new String[hold.length];
	      String[] hold_temp_ = new String[hold.length];
	      
	      String[] hold2_temp = new String[hold.length];
	      
	      int[] hold_tempo = new int[hold.length]; 
	      int[] hold2_tempo = new int[hold.length];
	      int[] hold_tempo_ = new int[hold.length];
	      int track = 0, track_ = 0;

  	  track = 0; track_ = 0; one_five = 0;
	      //get letters that starts with B and end with B	      
	      for(int x = 0; x< hold.length; x++){
	    	  if((hold[x].charAt(0)+"").equals("B")){
	    		  hold_temp[track] = hold[x]; track++;}
	    	  
	    	  if((hold[x].charAt(1)+"").equals("B")){
	    		  hold_temp_[track_] = hold[x];
	    		  track_++;}} 
	      
	    		  int val=0;
	      for(int x = 0; x< hold.length; x++){
	    	  
	    	  for(int r = 0; r<track_; r++){ 
 	    	  if((hold[x].charAt(1)+"").equals(hold_temp_[r].charAt(0)+""))
	    	  {hold2_temp[one_five] = hold[x];
	    	   hold_tempo_[val] = hold_int[x];
	    	  hold_tempo_[r] = hold_int[x]; one_five++;}
 	    	  
 	    	  }}
	      int min =0; String one = null, two = null, three = null;
	      for(int x =0; x< one_five; x++){
	
	    	  for(int r = 0; r<track; r++){

	    	  if((hold2_temp[x].charAt(0)+"").equals(hold_temp[r].charAt(1)+""))
	    	  {hold2_temp[min]=hold2_temp[x];
	    	  one = hold_temp[r];
	    	  two = hold2_temp[min];
	    	  three = hold_temp_[x];}
	      }}
	      
	      int newvalue = 0;
	      for(int x =0; x<hold.length; x++){
	    	  if(one.equals(hold[x])){newvalue+=hold_int[x]; }}
	      for(int x =0; x<hold.length; x++){
	    	  if(two.equals(hold[x])){newvalue+=hold_int[x];}}
	      for(int x =0; x<hold.length; x++){
	    	  if(three.equals(hold[x])){newvalue+=hold_int[x];}}	      
	    
	      System.out.println("output #9: "+newvalue);
	}
}
