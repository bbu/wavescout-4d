void draw_sphere ( float radius, int sectors )
{
	sectors = sectors < 2 ? 2 : sectors;
	float step = M_PI / 2.0f / sectors, i, j;

	glBegin ( GL_LINES );

	//for ( i = - M_PI / 2.0f; i < M_PI / 2.0f; i += step )
	for ( i = 0.0; i < M_PI / 2.0f; i += step )
	{
		for ( j = 0.0f; j < 2.0f * M_PI; j += step )
		{
			glVertex3f (
				radius * cos ( i ) * cos ( j ),
				radius * sin ( i ),
				radius * cos ( i ) * sin ( j )
			);

			glVertex3f (
				radius * cos ( i ) * cos ( j + step ),
				radius * sin ( i ),
				radius * cos ( i ) * sin ( j + step )
			);

			glVertex3f (
				radius * cos ( i ) * cos ( j ),
				radius * sin ( i ),
				radius * cos ( i ) * sin ( j )
			);

			glVertex3f (
				radius * cos ( i + step ) * cos ( j ),
				radius * sin ( i + step ),
				radius * cos ( i + step ) * sin ( j )
			);
		}
	}
 	glEnd ( );
}
