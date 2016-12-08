//FileName:		SETTree.c
//Project:		ast_assign6
//Author:		Alex Guerrero	
//Date:			March 26, 2014
//Description:	This program takes a directory path as a command line argument and
//				displays the direcotry hierarchy using findfirstfile(),findnextfile()
//				and findclose(). Files located inside a directory are indented and directories
//				are indented from the parent directory path.



//Include files
#include<Windows.h>
#include<stdio.h>
#include<string.h>



//disables warnings
#pragma warning( disable: 4996 )



//defined constants
#define ONE 1
#define BUFSIZE 1024


//prototype
int ListDirectoryContents( const char *path );



int main( int argc, char *argv[] )
{
	//variables, buffer for path
	char path[BUFSIZE] = {0};
	
	//if argument count is correct (2)
	if( argc == 2)
	{
		//copy argument to path buffer
		strcpy( path, argv[ONE] );
		//display the search directory
		printf( "List directory: %s\n", path );
		//list contents
		ListDirectoryContents( path );
	}
	//otherwise, if argument count is only 1
	else if( argc == 1 )
	{
		//display error to user
		printf("Usage: Directory path required\n");
	}
	//otherwise, if argument count is greater than 2
	else if( argc > 2) 
	{
		//display error to user
		printf("Usage: Invalid arguments\n");
	}

	return 0;
}



//FunctionName:	int ListDirectoryContents( const char *path )
//Project:		dsA1	
//Date:			March 28, 2014
//Parameters:	char* addressOfLastCharacter, char *p, char* buffer, char* finalString
//Description:	This function uses findFirstFile(), FindNextFile() and FincClose() to search through a specified
//				directory supplied by the user through a command line argument.  The path is processed by appending
//				"*.*" to the string and calling findfirstfile().  If the path is not found the user is informed.
int ListDirectoryContents( const char *path )
{
	//variables initialized
	WIN32_FIND_DATA fileData = { 0 };
    HANDLE h = NULL;
	int exit = 0;
	char newPath[BUFSIZE] = {0};
	char *addressOfLastCharacter = NULL;

    //append the wild cards to search for everything
    sprintf( newPath, "%s\\*.*", path );

	while(ONE)
	{
		//if h is Invalid_Handle_Value, path supplied was not found
		if( ( h = FindFirstFile( newPath, &fileData ) ) == INVALID_HANDLE_VALUE )
		{
			//inform user that the path was not found
			//set exit to 1 and exit the program
			printf( "Path not found: [%s]\n", path );	
			exit = 1;
			break;
		}
		do
		{
			//if you come across"." and "..", do nothing, otherwise...
			if( ( strcmp( fileData.cFileName, ".") != 0 ) && ( strcmp( fileData.cFileName, ".." ) != 0 ) )
			{
				//add the filename to the directory path supplied by the user after the backslash is appended
				sprintf( newPath, "%s\\%s", path, fileData.cFileName );

				//check to determine if we are dealing with a directory
				if( ( fileData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) != 0 ) 
				{
					//recursive call.....
					//if first file is a directory, display the directory to the screen and call ListDirectoryContents() to display files found inside this directory
					printf("   -%s\n", fileData.cFileName );
					ListDirectoryContents( newPath ); 
				}
				else
				{
					//otherwise first file is a file, print to screen with 6 spaces
					printf( "      _%s\n", fileData.cFileName );
				}
			}
		}
		//while there are files still to locate, repeat process
		while( FindNextFile( h, &fileData ) ); 
	
		break;//break out of the loop when there is nothing more to find
		
	}
	//close the file handle
    FindClose( h ); 

	//return the exit value, 0 means no errors occurred, 1 means a path was not found
    return exit;
}
