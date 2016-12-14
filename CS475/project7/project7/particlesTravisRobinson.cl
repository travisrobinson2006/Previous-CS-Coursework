typedef float4 point;
typedef float4 vector;
typedef float4 color;
typedef float4 sphere;


vector
Bounce( vector in, vector n )
{
	vector out = in - 2.*n*dot(in.xyz, n.xyz);
	out.w = 0.;
	return out;
}

vector
BounceSphere( point p, vector in, sphere s )
{
	vector n;
	n.xyz = fast_normalize( p.xyz - s.xyz );
	n.w = 0.;
	return Bounce( in, n );
}

bool
IsInsideSphere( point p, sphere s )
{
	float r = fast_length( p.xyz - s.xyz );
	return  ( r < s.w );
}

color
ChangeColor(color c)
{
	if(c.z != 0.)
	{
		c.x = 1.;
		c.y = 0.;
		c.z = 0.;
	}
	else if (c.x != 0.)
	{
		c.x = 0.;
		c.y = 1.;
		c.z = 0.;
	}
	else
	{
		c.x = 0.;
		c.y = 0.;
		c.z = 1.;
	}
	return c;
}

kernel
void
Particle( global point *dPobj, global vector *dVel, global color *dCobj )
{
	const float4 G       = (float4) ( 0., -9.8, 0., 0. );
	const float  DT      = .1;

	const sphere Sphere1 = (sphere)( -0., -800., 0.,  200. );
	const sphere Sphere2 = (sphere)( 1200., -800., 0.,  200. );
	const sphere Sphere3 = (sphere)( -1200., -600., 0.,  200. );
	const sphere Sphere4 = (sphere)( 0., -800., 1200.,  200. );
	const sphere Sphere5 = (sphere)( 0., -800., -1200.,  200. );

	int gid = get_global_id( 0 );

	point  p = dPobj[gid];
	vector v = dVel[gid];
	color c = dCobj[gid];

	point  pp = p + v*DT + .5*DT*DT*G;
	vector vp = v + G*DT;
	pp.w = 1.;
	vp.w = 0.;

	if( IsInsideSphere( pp, Sphere1 ) )
	{
		vp = BounceSphere( p, v, Sphere1 );
		pp = p + vp*DT + .5*DT*DT*G;
		c = ChangeColor(c);
	}
	else if( IsInsideSphere( pp, Sphere2 ) )
	{
		vp = BounceSphere( p, v, Sphere2 );
		pp = p + vp*DT + .5*DT*DT*G;
		c = ChangeColor(c);
	}
	else if( IsInsideSphere( pp, Sphere3 ) )
	{
		vp = BounceSphere( p, v, Sphere3 );
		pp = p + vp*DT + .5*DT*DT*G;
		c = ChangeColor(c);
	}
	else if( IsInsideSphere( pp, Sphere4 ) )
	{
		vp = BounceSphere( p, v, Sphere4 );
		pp = p + vp*DT + .5*DT*DT*G;
		c = ChangeColor(c);
	}
	else if( IsInsideSphere( pp, Sphere5 ) )
	{
		vp = BounceSphere( p, v, Sphere5 );
		pp = p + vp*DT + .5*DT*DT*G;
		c = ChangeColor(c);
	}

	dPobj[gid] = pp;
	dVel[gid]  = vp;
	dCobj[gid] = c;
}
