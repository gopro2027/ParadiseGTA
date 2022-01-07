#ifdef atoffileused

#define PZERO 38			/* index of 1e0 in powten[]	*/
#define PMAX 76				/* highest index of powten[]	*/
#define HUGE_NOR 1.70141183460469228		/* normalised HUGE	*/
double atofff(char s[]) /* convert string s to double */
{
	double powten[PMAX];
	for (int i = 0; i < PMAX; i++) {//initialize powten
		powten[i] = math::Pow(1,i-PZERO);
	}
    double val;
    int i, j, sign, esign, ex, ex1;

/* skip white space */
    for (i=0; s[i]==' ' || s[i]=='\n' || s[i]=='\t'; i++);
/* set sign to be +1 or -1 */
    sign = 1;
    if (s[i] == '+' || s[i] == '-')    /* sign */
	sign = (s[i++]=='+') ? 1 : -1;
/* read digits and build value for as long as there are digits */
    ex = PZERO - 1;
    for (val = 0.0, j = PZERO; s[i] >= '0' && s[i] <= '9'; i++) {
	if (j >= 0)
	    val += powten[j] * (s[i] - '0');
	j--;
	ex++;
    }
/* if first non-digit is decimal point skip it and keep going */
/* if it is not a decimal point we fall through to test for exponent */
    if (s[i] == '.')
	i++;
/* continue to build value while the digits keep coming */
    for (; s[i] >= '0' && s[i] <= '9'; i++){
	if (j >= 0)
	    val += powten[j] * (s[i] - '0');
	j--;
    }
/* if non-digit was an exponent flag deal with exponent */
    if (s[i]=='e' || s[i]=='E' || s[i]=='d' || s[i]=='D') {
	i++;
	esign = 1;
/* check for explicit + or - sign in exponent and deal with it */
	if (s[i] == '+' || s[i] == '-')
	    esign = (s[i++]=='+') ? 1 : -1;
	for (ex1 = 0; s[i] >= '0' && s[i] <= '9'; i++)
	    ex1 = 10 * ex1 + s[i] - '0';
	ex += ex1 * esign;
    }
/* incorporate exponent into val */
    if (ex < 0)
	val = 0.0;
    else if (ex < PMAX || (ex == PMAX && val < HUGE_NOR))
	val *= powten[ex];
    else {
	//cmemsg(FP_BIGI, s);
	val = (float)9999999999999999999;//HUGE;
    }
/* check that we have an acceptable termination; if not call error system
   before returning with what we have */
    //if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\0')
	//cmemsg(FP_BADC, s);
    return(sign * val);
}

char*  floatToString(float num)
{
   int whole_part = num;
   int digit = 0, reminder =0;
   int log_value = math::fastlog(num), index = log_value;
   long wt =0;

   // String containg result
   char str[30];

   //Initilise stirng to zero
   //memset(str, 0 ,20);

   //Extract the whole part from float num
   for(int  i = 1 ; i < log_value + 2 ; i++)
   {
       wt  =  math::Pow(10.0,i);
       reminder = whole_part  %  wt;
       digit = (reminder - digit) / (wt/10);

       //Store digit in string
       str[index--] = digit + 48;              // ASCII value of digit  = digit + 48
       if (index == -1)
          break;    
   }

    index = log_value + 1;
    str[index] = '.';

   float fraction_part  = num - whole_part;
   float tmp1 = fraction_part,  tmp =0;

   //Extract the fraction part from  num
   for( int i= 1; i < /*PRECISION*/10; i++)
   {
      wt =10; 
      tmp  = tmp1 * wt;
      digit = tmp;

      //Store digit in string
      str[++index] = digit +48;           // ASCII value of digit  = digit + 48
      tmp1 = tmp - digit;
   }    

   return str;
}
#endif