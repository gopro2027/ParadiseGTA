namespace math {
	float fmod(float num, float den) {
		return num - ((int)(num/den)) * den;
	}
	double constrainAngle(double x){
		x = fmod(x,360);
		if (x < 0)
		    x += 360;
		return x;
	}
	//convert to this asap http://pastebin.com/1xUJ5HFj
 
#define PI (3.1415926535897931)//(3.14159265359)
 
float DegreesToRadians(float Degrees)
{
        return Degrees * PI / 180.0f;
}
 
float RadiansToDegrees(float Radians)
{
        return Radians * 180.0f / PI;
}
 
float Factorial(int Value)
{
        int Ret = 1;
        for(int i = Value; i > 0; i--)
                Ret = Ret * i;
        return Ret;
}
 
float Pow(float Value, int Pow)
{
        float Ret = 1;
        for(int i = 0; i < Pow; i++)
                Ret = Ret * Value;
        return Ret;
}

unsigned int PowUI(unsigned int Value, unsigned int Pow)
{
        unsigned int Ret = 1;
        for(unsigned int i = 0; i < Pow; i++)
                Ret = Ret * Value;
        return Ret;
}
 
float SinTaylor(float AnglesDeg, float Accuracy)
{
 float AnglesRad = DegreesToRadians(AnglesDeg);
        float i = AnglesRad; float Ret = 0;
        bool Minus = false;
        for(int j = 1; j <= Accuracy; j += 2)
        {
                if(!Minus)
                        Ret += Pow(i,j)/Factorial(j);
                else
                        Ret -= Pow(i,j)/Factorial(j);
                Minus = !Minus;
        }
        return Ret;
}

float Sin(float x, float accuracy/*unused*/) {
	//step 1. get to [-180,180]
	while (x > 180)
		x -= 360;
	while (x < -180)
		x += 360;
	//step 2. calculate the sign - or +
	float absx = abs(x);
	int sign = x/absx;
	//step 3. get abs so it's [0,180]
	x = absx;
	return (float)(4*x*(180-x))/(40500-x*(180-x))*sign;
}
 
float Sin(float AnglesDeg) {
    return Sin(AnglesDeg, 16);//16
}
 
float Cos(float AnglesDeg,float Accuracy)
{
 float AnglesRad = DegreesToRadians(AnglesDeg);
 float Rad = (float)(PI/2.0f)-AnglesRad;
 float ang = RadiansToDegrees(Rad);
        return Sin(ang,Accuracy);
}
 
float Cos(float AnglesDeg) {
    return Cos(AnglesDeg,16);//16
}
 
float Tan(float AnglesDeg,float Accuracy)
{
        float sinus = Sin(AnglesDeg,Accuracy);
        float cosinus = Cos(AnglesDeg,Accuracy);
        return sinus/cosinus;
}
 
float Tan(float AnglesDeg) {
    return Tan(AnglesDeg,19);//19
}


	/*float abs(float value) {
		if (value < 0) {
			return value*-1;
		} else {
			return value;
		}
	}*/
 

	int ceil(float num) {
		int inum = (int)num;
		if (num == (float)inum) {
		    return inum;
		}
		return inum + 1;
	}
 
	int round(float f) {
		int i = (int)f;
		float tiny = f-i;
		if (tiny < 0.5f) {
			return i;
		} else {
			return i+1;
		}
	}

	/*float pow(float num, int power) {
		float ret = 1;
		for (int i = 0; i < power; i++)
			ret = ret*num;
		return ret;
	}*/

	//this new one works for negative numbets too lol
	#define abs(x) (x<0?-x:x)
	//template <typename T>
	//T abs(T val) {
	//	if (val < 0)
	//		return val * -1;
	//	return val;
	//}
	//#define abs(x) math::abs(x)
	float pow(float base,int pow) {
		float ret = 1;
		int absx = abs(pow);
		if (absx == pow)
			for (int i = 0; i < absx; i++)
				ret = ret*base;
		else
			for (int i = 0; i < absx; i++)
				ret = ret/base;
		return ret;
	}

	float root(float num, int nroot) {
		int iterations = 15 * (nroot-1);
		float x = iterations*100;
		for (int i = 1; i < iterations; i++) {
			x = (float)(((float)1/nroot)*(((nroot-1)*x)+(num/pow(x,nroot-1))));
		}
		return x;
	}

	//float dist(float x,float y,float z) {
	//	return root(x*x+y*y+z*z,2);
	//}

	__attribute__((naked)) void fast_squareRoot_compute(void *value) {
		__asm("lfs %f1, 0(%r3)");
		__asm("fsqrts %f1, %f1");
		__asm("stfs %f1, 0(%r3)");
		__asm("blr");
	}
	float fast_squareRoot(float value) {
		/*float store;
		store = value;
		fast_squareRoot_compute((void*)&store);
		return store;*/
		return root(value,2);
	}
	float distance(Vector3 a, Vector3 b) {
		float x = a.x-b.x;
		float y = a.y-b.y;
		float z = a.z-b.z;
		x *= x;
		y *= y;
		z *= z;
		return fast_squareRoot(x+y+z);
	}

	float dist(float x,float y,float z) {
		return fast_squareRoot(x*x+y*y+z*z);
	}

	float length(Vector3 loc1, Vector3 loc2) {
		float x = loc1.x-loc2.x;
		float y = loc1.y-loc2.y;
		float z = loc1.z-loc2.z;
		return root(x*x+y*y+z*z,2);
	}

	float atan2(float y, float x) {
		return GAMEPLAY::ATAN2(y,x);
	}
	float sin(float degrees) {
		return Sin(degrees);
	}
	float cos(float degrees) {
		return Cos(degrees);
	}
	float tan(float degrees) {
		return Tan(degrees);
	}
	float sqrt(float num) {
		return root(num,2);
	}


	/*
 float fastlog2(float x)  // compute log2(x) by reducing x to [0.75, 1.5)
{
    // a*(x-1)^2 + b*(x-1) approximates log2(x) when 0.75 <= x < 1.5
    const float a =  -.6296735;
    const float b =   1.466967;
    float signif, fexp;
    int exp;
    float lg2;
    union { float f; unsigned int i; } ux1, ux2;
    int greater; // really a boolean
 
    // get exponent
    ux1.f = x;
    exp = (ux1.i & 0x7F800000) >> 23;
    // actual exponent is exp-127, will subtract 127 later
 
    greater = ux1.i & 0x00400000;  // true if signif > 1.5
    if (greater) {
        // signif >= 1.5 so need to divide by 2.  Accomplish this by
        // stuffing exp = 126 which corresponds to an exponent of -1
        ux2.i = (ux1.i & 0x007FFFFF) | 0x3f000000;
        signif = ux2.f;
        fexp = exp - 126;    // 126 instead of 127 compensates for division by 2
        signif = signif - 1.0;                    // <
        lg2 = fexp + a*signif*signif + b*signif;  // <
    } else {
        // get signif by stuffing exp = 127 which corresponds to an exponent of 0
        ux2.i = (ux1.i & 0x007FFFFF) | 0x3f800000;
        signif = ux2.f;
        fexp = exp - 127;
        signif = signif - 1.0;                    // <<--
        lg2 = fexp + a*signif*signif + b*signif;  // <<--
    }
    // lines marked <<-- are common code, but optimize better
    //  when duplicated, at least when using gcc
    return(lg2);
}
*/
float fastlog22 (float x)
{
  union { float f; uint32_t i; } vx = { x };
  union { uint32_t i; float f; } mx = { (vx.i & 0x007FFFFF) | 0x3f000000 };
  float y = vx.i;
  y *= 1.1920928955078125e-7f;

  return y - 124.22551499f
           - 1.498030302f * mx.f 
           - 1.72587999f / (0.3520887068f + mx.f);
}

float fastlog (float x)
{
  return 0.69314718f * fastlog22 (x);
}
}
 
 
/* 
 
int main (char *args) {
    cout << math::Sin(90) << endl;
    cout << math::Cos(180) << endl;
    cout << math::Tan(90.1f) << endl;
}
 
//http://pastebin.com/jq1H307z

*/