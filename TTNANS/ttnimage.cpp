#include "ttndef.h"
#include "ttnpros.h"
#include "tmatrix.h"
#include "ttnui.h"

#define X(x) at(x,0)
#define Y(x) at(x,1)
#define R(x) at(x,2)
#define G(x) at(x,3)
#define B(x) at(x,4)
#define I(x) at(x,5)

#define U8BIT unsigned char

// #pragma pack (1)

void raw_image_import()
 {
 char filename [FILENAMELENGTH];
 
 GetFilename("Please select image file to import",filename,"*.raw",false);

 int width		= mrequest_int("Enter image width  (w<2000)");
 int height		= mrequest_int("Enter image height (h<2000)");
 int channels	= mrequest_int("Enter number of channels (0<c<4)");
 bool interleaved = mrequest_yn("Is the image interleaved ?");
 int header		= mrequest_int("Enter header size");
 
 if( (width > 0) AND
	 (width < 2000) AND
	 (height > 0) AND
	 (height < 2000) AND
	 (channels > 0) AND
	 (channels < 4) AND
	 (header >= 0) )
  {
  CTmatrix<DATA> matrix (width*height,6,0,"Image X,Y,c1(R),c2(G),c3(B),c4(I)");
  
  mprintf("Width       \t: %d \n",width);
  mprintf("Heigth      \t: %d \n",height);
  mprintf("Channels    \t: %d \n",channels);
  mprintf("Interleave  \t: %d \n",(int)interleaved);
  mprintf("Depth       \t: 8 bit (preset) \n");
  mprintf("Byte Order  \t: Intel - IBM PC (preset) \n");
  mprintf("Header Size \t: %d bytes \n",header);
  mprintf("\n\n");

  U8BIT * pbuffer;
  size_t buffersize = ( ( (width * height) * channels ) + header );
  FILE * stream;
  bool read_ok=true;

  if (sizeof(U8BIT) != 1)
   {
   mprintf( "Incorrect datatype sizes.\n" ); 
   return;
   }

  if ( (pbuffer=(U8BIT *)MMalloc(buffersize) ) == NULL)
   {
   mprintf( "Not enough memory.\n" ); 
   return;
   }
   
  if ((stream  = fopen( filename, "rb" )) == NULL )
   {
   mprintf( "The file was not opened.\n" ); 
   MFree(pbuffer);
   return;
   }

  mprintf( "Attempting to read %d bytes.\n",(int)(buffersize*sizeof(U8BIT)) ); 

  size_t  numread = fread(pbuffer, buffersize, 1, stream );

 /* 
  size_t numread = 0;

  for(unsigned x=0;x<buffersize;x++)
   {
   if(fread(&pbuffer[x], sizeof(U8BIT), 1, stream )==1)numread++;
   }
   mprintf("Read %d bytes.\n",numread);
   if(numread!=buffersize)numread=0;
  */

  if(numread != (size_t)1)
   {
   mprintf( "Wrong file size.\n",(int)numread);
   read_ok=false; 
   }

  if(read_ok)
   {
   unsigned at_buf,at_mat,x,y,c;
   at_mat=0;
   at_buf=header;

   if(interleaved)
    {
    for(y=0;y<height;y++)
    for(x=0;x<width;x++)
     {
     matrix.X(at_mat)=x;
     matrix.Y(at_mat)=y;
     for(c=0;c<channels;c++)
      { 
      matrix.at(at_mat,2+c)=(DATA)(pbuffer[at_buf]);
      at_buf++;
      }
     at_mat++;
     }
    }
   else
    {
    for(c=0;c<channels;c++)
     {
     for(y=0;y<height;y++)
     for(x=0;x<width;x++)
      {
      matrix.X(at_mat)=x;
      matrix.Y(at_mat)=y;
      matrix.at(at_mat,2+c)=(DATA)(pbuffer[at_buf]);
      at_buf++;
      at_mat++;
      }
     at_mat=0;
     }
    }
     
   mprintf("Read %d bytes.\n",at_buf);
   }

  MFree(pbuffer);
  fclose(stream);
  
  if(read_ok)
   {
   unsigned at_mat,x,y;
   at_mat=0;
   mprintf("Calculating simple intensity (c4)...");
   for(y=0;y<height;y++)
   for(x=0;x<width;x++)
    {
    matrix.I(at_mat)=(matrix.R(at_mat)+matrix.G(at_mat)+matrix.B(at_mat))/3;
    at_mat++;
    }
   mprintf("done.\n");
   matrix.show();
   matrix.save();
   }
  }
 else
  {
  mprintf("Can't continue. Check settings.\n");
  }
 }

void Image_Utility()
{
 {
 mprintf("Importing / Exporting Raw Image Format Files (*.RAW).\n");
 mhintclear();
 mhintf(false,"Adobe Photoshop (R) information follows:\n\n");
 mhintf(false,"\n");
 mhintf(false,"The Raw format is a flexible file format for transferring files between \n");
 mhintf(false,"applications and computer platforms. Raw format consists of a stream of  \n");
 mhintf(false,"bytes describing the color information in the file. Each pixel is described \n");
 mhintf(false,"in binary format, in which 0 equals black and 255 equals white.  \n");
 mhintf(false,"The header parameter is the number of bytes of information that will appear at the  \n");
 mhintf(false,"beginning of the file, before the actual image information. This value defines  \n");
 mhintf(false,"the number of zeros that will be placed at the beginning of the file as placeholders. \n");
 mhintf(false,"By default, there is no header (header size = 0). You can enter a header when you \n");
 mhintf(false,"open the file in the Raw format (see Opening Raw files). You can also save the file \n");
 mhintf(false,"without a header and then use a file-editing program, such as Norton Utilities \n");
 mhintf(false,"(Macintosh) or HEdit (Windows), to replace the zeros with header information. \n");
 mhintf(false,"You can choose to save the image in an interleaved or noninterleaved format. If you  \n");
 mhintf(false,"choose the interleaved format, the color values (red, green, and blue, for example) \n");
 mhintf(false,"are stored sequentially. The choice you make depends on the requirements of the application \n");
 mhintf(false,"you plan to use to open the file. \n");
 mhintf(false,"\n");
 }

int msel=-1;
char mtitle[]=" Image File Menu ";
char * menu[]={"0...Go Back.  ",
               "1...Import Raw Image File.",
               "2...Export Raw Image File.",
               };

while((TGBL no_error)&&(msel!=0))
 {
 msel=mmenu(mtitle,menu,3,2);
 switch(msel)
  {
  case 0: break;
  case 1: raw_image_import(); break;
  case 2: mprintf("Sorry, this feature is not implemented in this version.\n"); break;
  default:break;
  }
 }
}
