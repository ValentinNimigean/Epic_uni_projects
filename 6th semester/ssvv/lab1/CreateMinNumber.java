public class CreateMinNumber {
/**
* Subalgorithm getDigits1(givenNumber, numberOfDigits, valuesDigits)
* Extracts digits of givenNumber into valuesDigits (1-based index, LSB first).
* valuesDigits[1] = least significant digit, valuesDigits[numberOfDigits] = most significant digit.
* @param givenNumber the input number
* @param valuesDigits array to store digits (1-based; size should be >= number of digits + 1)
* @return numberOfDigits - the count of digits extracted
*/
static int getDigits1(int givenNumber, int[] valuesDigits) {
int i = 0;
while (givenNumber != 0) {
i = i + 1;
valuesDigits[i] = givenNumber % 10;
givenNumber = givenNumber / 10;
}
int numberOfDigits = i;
return numberOfDigits;
}
/**
* Subalgorithm buildNumber1(numberOfDigits, valuesDigits, newNumber)
* Rebuilds the minumum number with the digits from valuesDigits[1..numberOfDigits].
* @param numberOfDigits number of digits
* @param valuesDigits array of digits (1-based)
* @return newNumber - the newly formed number
*/
static int buildNumber1(int numberOfDigits, int[] valuesDigits) {
int newNumber = 0;
for (int i = 1; i <= numberOfDigits; i++) {
newNumber = newNumber * 10 + valuesDigits[i];
}
return newNumber;
}
public static void main(String[] args) {
if (args.length < 1) {
System.err.println("Usage: java DetCifre <number>");
System.exit(1);
}
int givenNumber = Integer.parseInt(args[0]);
// valuesDigits is 1-based; allocate enough space for digits + index offset
int[] valuesDigits = new int[20];
System.out.println("Original number : " + givenNumber);
// Extract digits
int numberOfDigits = getDigits1(givenNumber, valuesDigits);
System.out.println("Number of digits: " + numberOfDigits);
for (int i = 1; i <= numberOfDigits; i++) {
System.out.print(valuesDigits[i] + " ");
}
System.out.println();
int newNumber = buildNumber1(numberOfDigits, valuesDigits);
System.out.println("Minimum number formed with the same digits : " + newNumber);
}
}
=