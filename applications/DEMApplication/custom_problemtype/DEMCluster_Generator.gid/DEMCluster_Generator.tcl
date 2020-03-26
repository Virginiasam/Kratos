## GiD events --------------------------------------------------------------------------------------------------------------------------------------------------

proc InitGIDProject { dir } {

    # Create buttons for calculate mass, center of mass and inertia later on.
    # if { [GidUtils::IsTkDisabled] eq 0} {
    #     GiDMenu::Create "Sphere Cluster Creation" PRE
    #     GiDMenu::InsertOption "Sphere Cluster Creation" [list "Inertia"] 0 PRE "GidOpenConditions \"Inertia\"" "" ""
    #     GiDMenu::UpdateMenus
    # }

    # Load the application scripts
    set scripts_dir [file join $dir .. .. ]
    # set tcl_filename [file join $scripts_dir scripts initptype.tcl]
    # if {[catch {source $tcl_filename} msg]} {
    #     WarnWinText $msg
    #     return 1
    # }
}

#-------------------------------------------------------------------------------

proc BeforeMeshGeneration {elementsize} {
    W "execute BeforeMeshGeneration"

}

proc AfterMeshGeneration {fail} {
    W "execute AfterMeshGeneration"
    #::CalculateInertia
}

#-------------------------------------------------------------------------------

proc BeforeRunCalculation { batfilename basename dir problemtypedir gidexe args } {

    # Write file
    source [file join $problemtypedir file.tcl]
}

#-------------------------------------------------------------------------------

# sintaxis reference:
# proc NormalTranslationMatrix {Vertex Point1 Point2 Distance} {
#     # Vector in local x direction
#     set Vx(0) [expr {[lindex $Point1 1]-[lindex $Vertex 1]}]
#     set Vx(1) [expr {[lindex $Point1 2]-[lindex $Vertex 2]}]
#     set Vx(2) [expr {[lindex $Point1 3]-[lindex $Vertex 3]}]

#     # Vector in local y direction
#     set Vy(0) [expr {[lindex $Point2 1]-[lindex $Vertex 1]}]
#     set Vy(1) [expr {[lindex $Point2 2]-[lindex $Vertex 2]}]
#     set Vy(2) [expr {[lindex $Point2 3]-[lindex $Vertex 3]}]

#     # Vector in local z direction (Cross product between Vx and Vy)
#     set Vz(0) [expr {$Vx(1)*$Vy(2)-$Vx(2)*$Vy(1)}]
#     set Vz(1) [expr {$Vx(2)*$Vy(0)-$Vx(0)*$Vy(2)}]
#     set Vz(2) [expr {$Vx(0)*$Vy(1)-$Vx(1)*$Vy(0)}]
#     set InvNorm [expr {1.0/sqrt($Vz(0)*$Vz(0)+$Vz(1)*$Vz(1)+$Vz(2)*$Vz(2))}]
#     set Vz(0) [expr {$Vz(0)*$InvNorm}]
#     set Vz(1) [expr {$Vz(1)*$InvNorm}]
#     set Vz(2) [expr {$Vz(2)*$InvNorm}]

#     set Tx [expr {$Distance*Vz(0)}]
#     set Ty [expr {$Distance*Vz(1)}]
#     set Tz [expr {$Distance*Vz(2)}]

#     return [list 1.0 0.0 0.0 $Tx \
#                  0.0 1.0 0.0 $Ty \
#                  0.0 0.0 1.0 $Tz \
#                  0.0 0.0 0.0 1.0]

# }


proc CalculateInertia {Vertex Point1 Point2 Distance} {
    pseudo:
    
    1.- calculate total volume from tetrahedras:
    tris: number of triangles
        for each triangle
        triple producto de los vertices de cada uno.
        volume += Determinant(float3x3(vertices[tris[i][0]],vertices[tris[i][1]],vertices[tris[i][2]]));
    return volume/6.0;  // since the determinant give 6 times tetra volume


    2.- center of mass:
		for each triangle:
			float3x3 A(vertices[tris[i][0]],vertices[tris[i][1]],vertices[tris[i][2]]);  
			vol=Determinant(A)
			com += vol * (A.x+A.y+A.z);
			volume+=vol;
        com /= volume*4.0;     


    3.- inertia tensor:
        # // count is the number of triangles (tris) 
		# // The moments are calculated based on the center of rotation com which you should calculate first
		# // assume mass==1.0  you can multiply by mass later.

		float  volume=0;                          // technically this variable accumulates the volume times 6
		float3 diag(0,0,0);                       // accumulate matrix main diagonal integrals [x*x, y*y, z*z]
		float3 offd(0,0,0);                       // accumulate matrix off-diagonal  integrals [y*z, x*z, x*y]
		for each triangle
		{
			float3x3 A(vertices[tris[i][0]]-com,vertices[tris[i][1]]-com,vertices[tris[i][2]]-com);
			d = Determinant(A);  // vol of tiny parallelapiped= d * dr * ds * dt (the 3 partials of my tetral triple integral eq)
			volume +=d;                   // add vol of current tetra (note it could be negative - that's ok)
			for(int j=0;j < 3;j++)
			{
				int j1=(j+1)%3;   
				int j2=(j+2)%3;   
				diag[j] += (A[0][j]*A[1][j] + A[1][j]*A[2][j] + A[2][j]*A[0][j] + 
				            A[0][j]*A[0][j] + A[1][j]*A[1][j] + A[2][j]*A[2][j]  ) *d; // divide by 60.0f later;

				offd[j] += (A[0][j1]*A[1][j2]  + A[1][j1]*A[2][j2]  + A[2][j1]*A[0][j2]  +
				            A[0][j1]*A[2][j2]  + A[1][j1]*A[0][j2]  + A[2][j1]*A[1][j2]  +
				            A[0][j1]*A[0][j2]*2+ A[1][j1]*A[1][j2]*2+ A[2][j1]*A[2][j2]*2 ) *d; // divide by 120.0f later
			}
		}
		diag /= volume*(60.0f /6.0f);  // divide by total volume (vol/6) since density=1/volume
		offd /= volume*(120.0f/6.0f);
		return float3x3(diag.y+diag.z  , -offd.z      , -offd.y,
					-offd.z        , diag.x+diag.z, -offd.x,
					-offd.y        , -offd.x      , diag.x+diag.y );








  # alternative method:  calculate Moments of inertia tensor
  double Ixx=0, Iyy=0, Izz=0, Ixy=0, Ixz=0, Iyz=0, x, y, z, m, mtot=0.0;
  double Rcom[3] = { 0.0, 0.0, 0.0 };
  for (i=0; i<numCartesians; i++) {
    x = cartCoords[i][0];
    y = cartCoords[i][1];
    z = cartCoords[i][2];
    m = masslist[i];

    // Center of mass
    Rcom[0] += m*x;
    Rcom[1] += m*y;
    Rcom[2] += m*z;
    mtot += m;
    Ixx += m*(y*y+z*z);
    Iyy += m*(x*x+z*z);
    Izz += m*(x*x+y*y);
    Ixy -= m*x*y;
    Ixz -= m*x*z;
    Iyz -= m*y*z;
  }

}


# extra reference:
# Here is how to compute Volume:

	
# 	float Volume(const float3 *vertices, const int3 *tris, const int count) 
# 	{
# 		// count is the number of triangles (tris) 
# 		float  volume=0;
# 		for(int i=0; i < count; i++)  // for each triangle
# 		{
# 			volume += Determinant(float3x3(vertices[tris[i][0]],vertices[tris[i][1]],vertices[tris[i][2]])); //divide by 6 later for efficiency
# 		}
# 		return volume/6.0f;  // since the determinant give 6 times tetra volume
# 	}
 	
	
	
# Here is how to compute Center Of Mass:

	
# 	float3 CenterOfMass(const float3 *vertices, const int3 *tris, const int count) 
# 	{
# 		// count is the number of triangles (tris) 
# 		float3 com(0,0,0);
# 		float  volume=0; // actually accumulates the volume*6
# 		for(int i=0; i < count; i++)  // for each triangle
# 		{
# 			float3x3 A(vertices[tris[i][0]],vertices[tris[i][1]],vertices[tris[i][2]]);  
# 			float vol=Determinant(A);  // dont bother to divide by 6 
# 			com += vol * (A.x+A.y+A.z);  // divide by 4 at end
# 			volume+=vol;
# 		}
# 		com /= volume*4.0f; 
# 		return com;
# 	}

	
	
	
# Here is how to compute Inertial Tensor:

	
# 	float3x3 Inertia(const float3 *vertices, const int3 *tris, const int count, const float3& com)  
# 	{
# 		// count is the number of triangles (tris) 
# 		// The moments are calculated based on the center of rotation com which you should calculate first
# 		// assume mass==1.0  you can multiply by mass later.
# 		// for improved accuracy the next 3 variables, the determinant d, and its calculation should be changed to double
# 		float  volume=0;                          // technically this variable accumulates the volume times 6
# 		float3 diag(0,0,0);                       // accumulate matrix main diagonal integrals [x*x, y*y, z*z]
# 		float3 offd(0,0,0);                       // accumulate matrix off-diagonal  integrals [y*z, x*z, x*y]
# 		for(int i=0; i < count; i++)  // for each triangle
# 		{
# 			float3x3 A(vertices[tris[i][0]]-com,vertices[tris[i][1]]-com,vertices[tris[i][2]]-com);  // matrix trick for volume calc by taking determinant
# 			float    d = Determinant(A);  // vol of tiny parallelapiped= d * dr * ds * dt (the 3 partials of my tetral triple integral equasion)
# 			volume +=d;                   // add vol of current tetra (note it could be negative - that's ok we need that sometimes)
# 			for(int j=0;j < 3;j++)
# 			{
# 				int j1=(j+1)%3;   
# 				int j2=(j+2)%3;   
# 				diag[j] += (A[0][j]*A[1][j] + A[1][j]*A[2][j] + A[2][j]*A[0][j] + 
# 				            A[0][j]*A[0][j] + A[1][j]*A[1][j] + A[2][j]*A[2][j]  ) *d; // divide by 60.0f later;
# 				offd[j] += (A[0][j1]*A[1][j2]  + A[1][j1]*A[2][j2]  + A[2][j1]*A[0][j2]  +
# 				            A[0][j1]*A[2][j2]  + A[1][j1]*A[0][j2]  + A[2][j1]*A[1][j2]  +
# 				            A[0][j1]*A[0][j2]*2+ A[1][j1]*A[1][j2]*2+ A[2][j1]*A[2][j2]*2 ) *d; // divide by 120.0f later
# 			}
# 		}
# 		diag /= volume*(60.0f /6.0f);  // divide by total volume (vol/6) since density=1/volume
# 		offd /= volume*(120.0f/6.0f);
# 		return float3x3(diag.y+diag.z  , -offd.z      , -offd.y,
# 					-offd.z        , diag.x+diag.z, -offd.x,
# 					-offd.y        , -offd.x      , diag.x+diag.y );
# 	}
	