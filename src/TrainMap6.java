
public class TrainMap6 {
	
	public void result(){
    String [] hold = {"AB", "BC", "CD", "DC", "DE", "AD", "CE", "EB", "AE"};
    int[] hold_int = {5,4,8,8,6,5,2,3,7};
    
    String hold2 = "ABBCCDDCDEADCEEBAE";
    String line ="";
    
    String[] hold_temp = new String[hold.length];
    String[] hold_temp_ = new String[hold.length];
    
    
    int track = 0, track_ = 0;

    	      

//reinitialiaze variables
track = 0;  	  
hold_temp = new String[hold.length];
line="";


//get letters that includes C
for(int x =0; x<hold.length; x++){
	  if(hold[x].contains("C")){
		  hold_temp[track] = hold[x];
		  line = line +""+ hold_temp[track]+""; track++;}}

track = 0;
//get rid of duplicate letters except c
for(int x =0; x<line.length(); x++){    	  
	  hold_temp[track] = line.charAt(x)+"";track++;}

line ="";
for(int x =0; x<hold_temp.length; x++){  
	  if(x == hold_temp.length-1){break;}
	  if(hold_temp[x].equals(hold_temp[x+1])){
		  hold_temp[x] = ""; }}

for(int x =0; x<hold_temp.length; x++){
	  if(hold_temp[x] == null){hold_temp[x]="";}
	  line = line +""+ hold_temp[x]+"";}

track = 0;
track_ =0;
hold_temp = new String[line.length()];
hold_temp_ = new String[line.length()];

//2 stops trips that start at c and end at c  
for(int x =0; x<line.length(); x++){
	  if(x == hold_temp.length-1 || x == hold_temp.length-2){break;}
	  if(line.charAt(x)=='C' && line.charAt(x+2)=='C')
	  {hold_temp[track]=line.charAt(x) + ""+ line.charAt(x+1) +""+ line.charAt(x+2); track++;}}

//reverse line
for(int x =line.length()-1; x>=0; x--){
	  hold_temp_[track_] = line.charAt(x)+""; track_++;}

line ="";
for(int x =0; x<track_; x++){
	  if(hold_temp_[x].equals("C")){hold_temp_[x]="";}
	  line = line +""+ hold_temp_[x];}

hold_temp_ = new String[line.length()];
track_ =0;

//group letters in 2
for(int x = 0; x< line.length()-1; x++){
	  if(x == line.length()-1){break;}
	  
	  for(int r = 1; r < line.length(); r++){
	  hold_temp_[track_] = line.charAt(x) +""+ line.charAt(x+r);
	  track_++;
	  if(track_ ==line.length()){break;}}}


//compare letters to given letters
for(int r =0; r<hold_temp_.length; r++){			  
	  if((hold2.contains(hold_temp_[r]))) {
		  hold_temp[track] = "C"+hold_temp_[r]+"C"; track++;}}

System.out.println("output #6: "+track);
//for(int r =0; r<track; r++){
//	  System.out.print(hold_temp[r]+", ");}
}}
