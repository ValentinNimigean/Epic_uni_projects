public class LongestPrimeSequence {
private ArrayList l;
 private int start, length;
 public LongestPrimeSequence(){
 System.out.println("Long. Seq. empty ...");
 }
 public void setSequence(ArrayList l){
 this.l=l;
 }
 public LongestPrimeSequence(ArrayList newL){
 this.l = newL;
 this.start=-1;
 this.length=0;
 }
 public int getStart(){return this.start;}
 public int getLength(){return this.length;}
 public boolean isPrime(int n) throws ValueException{
 boolean b = true;
 if(n<0){
 throw new ValueException("data not valid");
 }
 if(n<2){
 b=false;
 }
 else{
 int i=2;
 while (i< (n/2)){
 if ((n % i) == 0){
 b=false;
 }
 else
 b=true;
 i++;
 }
 }
 return b;
 }
 public void SolveLongestSequence() throws ValueException{
 int posI=-1, lengthI=0, i=0;
 int posF=-1, lengthF=0;
 while(i<this.l.size()){
 if(isPrime((int)this.l.get(i))==true){
 if(posI==-1){
 posI=i;
 lengthI=1;
 }
 else 
 lengthI++;
 }
 else{
 if(lengthI>lengthF){
 lengthF=lengthI;
 posF = posI;
 }
 }
 i++;
}
 this.start =posF;
 this.length=lengthF;
 }
 }