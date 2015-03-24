package enum1;

 
public class EnumExample1 {
 
public enum Company {
EBAY, PAYPAL, GOOGLE, YAHOO, ATT
}
 
Company cName;
 
public EnumExample1(Company cName) {
this.cName = cName;
}
 
public void companyDetails() {
switch (cName) {
case EBAY:
System.out.println("Biggest Market Place in the World.");
break;
 
case PAYPAL:
System.out.println("Simplest way to manage Money.");
break;
 
case GOOGLE:
case YAHOO:
System.out.println("1st Web 2.0 Company.");
break;
 
default:
System.out.println("Google - biggest search giant.. ATT - my carrier provider..");
break;
}
}
 
public static void main(String[] args) {
EnumExample1 ebay = new EnumExample1(Company.EBAY);
ebay.companyDetails();
EnumExample1 paypal = new EnumExample1(Company.PAYPAL);
paypal.companyDetails();
EnumExample1 google = new EnumExample1(Company.GOOGLE);
google.companyDetails();
EnumExample1 yahoo = new EnumExample1(Company.YAHOO);
yahoo.companyDetails();
EnumExample1 att = new EnumExample1(Company.ATT);
att.companyDetails();
}
}
