# Digital-Signature-Std-Assignment-6_CS6530
Digital Signature Standard (DSS) Assignment-6 Cryptography.

Name- Ayub Shaikh \n
Roll Number:- CS21M515 
Email-Id - Ayub.Shaikh.Vahid@gmail.com

The program is in C- language. name of program file is-
**DigitalSignaturesStdAlgo.c**

-----------------------------------------------------------------------------------------------------------------
**THIS Code is already compiled on this and uploded in this online Compiler  https://onlinegdb.com/4ZCsS6i8a
Just click on this link( https://onlinegdb.com/4ZCsS6i8a ) it will take you to the project there you can directly RUN the program i have uploded same code 
in this compiler you can check the code and name it was creted by me so that it is easy for you to verify insted runing .exe or creating .exe. 👍 **
------------------------------------------------------------------------------------------------------------------------------------


To generate binary EXE file use this command
- gcc DigitalSignaturesStdAlgo.c -o DSS -lgmp
- 
and then run the exe.
or dirctly compile the program DigitalSignaturesStdAlgo.c and sha_256.h programs it will run the 
We can use the online c compiler to Run this as well just add these 2 files DigitalSignaturesStdAlgo.c and sha_256.h
and it will run the program easy way.( online compiler to run the program https://www.onlinegdb.com/online_c_compiler)

**Sample Output 1 :**
1. Enter the message: any number can enter belwo is example msg is- 123456789
2. then program do the key gernartion and signature generation as per screen shot.
![image](https://user-images.githubusercontent.com/94394753/145401172-a7b91606-1546-4343-a5ab-dc15e99a9ae4.png)

3. Now to verfiy the Signature belwo is screen shot
4. we enter the same message which entered initially to check - msg is- **123456789**
5. then we enter the r and s to verify Signature as below screen shot we enter correct data of r and s
 and message and signature is same so it gives the Successful message 👍 as per belwo screen shot
**SIGNATURE VERIFICATION IS SUCCESSFULL!!!!!!!!!!!!!!... ACCEPTED..!! :-) :-) **
![image](https://user-images.githubusercontent.com/94394753/145401562-055e3043-ac5d-4a0f-b29c-1e2f1caf7069.png)

**Sample Output 2 :**
1. Test number message is entered is **778877**
![image](https://user-images.githubusercontent.com/94394753/145403482-ae3c31db-0057-4e87-a0e9-71de84e1ef19.png)
2. Now we pass the wrong message **33333** to check with correct r and s values as per below screen shot
 it reject the message with 
 Message received is INVALID..
 SIGNATURE VERIFICATION IS FAILED!!!!!!!!!!!!!!... REJECTED..!! 👎
![image](https://user-images.githubusercontent.com/94394753/145404067-1e9fa1d8-3a31-40cc-9dcb-bd229a7bf165.png)

Sample Output 3 :
any number entered 9998 then program do the key gernartion and signature generation as per screen shot.
![image](https://user-images.githubusercontent.com/94394753/145405136-8a0bc24e-ce91-41a6-8108-217ff94d87b1.png)
Now we will pass the worong value of Signature r as 1111111 just any value So as we are passing signature value 
Wrong it fails the verification and gives this message: **SIGNATURE VERIFICATION IS FAILED!!!!!!!!!!!!!!... REJECTED..!! ** 
below is screen shot of this
![image](https://user-images.githubusercontent.com/94394753/145405587-844f8f29-928b-4105-aa0e-5df8b52e12d6.png)

**Sample output 3**
Test number message is entered is **5555**
![image](https://user-images.githubusercontent.com/94394753/145406558-96984eda-6b66-45a7-ae02-9fda1b9008c8.png)

Now we will enter the wrong value of signature s as just 123 somthing as shown in belwo screenshot so it will fail the 
SIgnature validation as per belwo screen shot.**SIGNATURE VERIFICATION IS FAILED!!!!!!!!!!!!!!... REJECTED..!! ** 
![image](https://user-images.githubusercontent.com/94394753/145406899-774afbe9-5589-4ca1-bb11-4ada6c196ced.png)

Sample out put 4
We will enter any number 
![image](https://user-images.githubusercontent.com/94394753/145407631-35d24510-4de5-4a80-881b-97d30686d5a7.png)
Then we will verify by entering the CORRECT message number and Correct SIGNATURE values r and s , SO we get successful message as belwo.
![image](https://user-images.githubusercontent.com/94394753/145408046-ba8323c9-d34c-42ef-b6cc-98e7e7a4cc4b.png)


