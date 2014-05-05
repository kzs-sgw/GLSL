
// simple.vert

void main( void )
{
  gl_FrontColor = vec4( 1.0, 0.0, 0.0, 1.0 );
  gl_Position = ftransform();
}
