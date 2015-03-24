package enum1;

//An enumeration of apple varieties. 
enum Apple { Jonathan, GoldenDel, RedDel, Winesap, Cortland }
enum Drink  {Sprite(2); private int price; 
Drink(int p){price = p;} int getPrice(){return price;}}

class EnumExample_values{ 
	public static void main(String args[]) { 
		Apple ap = null;
System.out.println("Here are all Apple constants:");
//use values() 
Apple allapples[] = Apple.values(); 
for(Apple a : allapples) 
	System.out.println(a);
System.out.println();
//use valueOf() 
try {ap = Apple.valueOf("Winesap");}
catch(Exception e){System.out.println("not found");}
System.out.println("ap contains " + ap);
System.out.println("price of Sprite is: $"+Drink.Sprite.getPrice());
}
} 
