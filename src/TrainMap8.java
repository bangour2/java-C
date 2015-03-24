
public class TrainMap8 {

	public void result(){
	      String [] hold = {"AB", "BC", "CD", "DC", "DE", "AD", "CE", "EB", "AE"};
	      int[] hold_int = {5,4,8,8,6,5,2,3,7};
	      	      
	      String[] hold_temp = new String[hold.length];
	      String[] hold_temp_ = new String[hold.length];
	      
	      int[] hold_tempo = new int[hold.length]; 
	      int[] hold_tempo_ = new int[hold.length];
	      int track = 0, track_ = 0;

	      	      
	      //get letters that starts with A and end with C	      
	      for(int x = 0; x< hold.length; x++){
	    	  if((hold[x].charAt(0)+"").equals("A")){
	    		  hold_temp[track] = hold[x];
	    		  hold_tempo[track] = hold_int[x]; track++;}
	    	  
	    	  if((hold[x].charAt(1)+"").equals("C")){
	    		  hold_temp_[track_] = hold[x];
	    		  hold_tempo_[track_] = hold_int[x];track_++;}}
	      
	    
	      int newvalue = track*track_; int value =0;
	      String[] hold2_temp = new String[newvalue];
	      int[] hold2_tempo = new int[newvalue];
	            
	      //combine A letters with C letters
	      for(int x = 0; x< track; x++){	    	  
	    	  for(int r = 0; r<track_; r++){
	    		  hold2_temp[value] = hold_temp[x]+""+hold_temp_[r];
	    		  hold2_tempo[value] = hold_tempo[x]+hold_tempo_[r];
	    		  value++;
	    	  }}
	     
	      
	      //store previous operations where the 2 letters in AC are the same
	      track = 0; track_ = 0;
	      for(int x = 0; x< value; x++){
	    	  
	    	  if((hold2_temp[x].charAt(1)+"").equals((hold2_temp[x].charAt(2)+""))){
	    		  
	    		  hold2_temp[track] = hold2_temp[x];
	    		  hold2_tempo[track] = hold2_tempo[x];
	    		  track++;
	    		  
	    	  }}
	      	    	  
	          //shortest distance
	      int min = hold2_tempo[0];
	  	int max = hold2_tempo[0];
	   
	  	for (int x = 1; x <= hold2_tempo.length - 1; x++) {
	  		if (max < hold2_tempo[x]) {
	  			max = hold2_tempo[x];
	  		}
	   
	  		if (min > hold2_tempo[x]) {
	  			min = hold2_tempo[x];
	  		}
	  	}
	    	  
	    	  System.out.println("output #8: "+ min);
	}
}
