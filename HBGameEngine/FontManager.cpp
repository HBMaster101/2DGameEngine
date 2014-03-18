////////////////////////////////////////
//File:              <FontManager.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/10/14>
//Date Modified:     <3/10/14>
//Brief:             <Font Manager Code>
////////////////////////////////////////
#include "FontManager.h"
FontManager::FontManager(void)
{
	//Call glGenBuffers once for
	glGenBuffers(1,&PositionBuffer);//Position
	glGenBuffers(1,&ColorBuffer);//Color
	glGenBuffers(1,&UVBuffer);//UVs
	glGenBuffers(1,&MatrixBuffer);//and Matrix
}
FontManager::~FontManager(void)
{
}
//Load the Font Sheet
void FontManager::LoadFont(const char * a_pFontSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	char ch;
	doc.LoadFile(a_pFontSheet);
	rootNode = doc.FirstChildElement("TextureAtlas");
	currentNode = rootNode;
	//
	childElement = currentNode->ToElement();
	FontAtlas.sSheet = childElement->Attribute("imagePath");
	FontAtlas.v2Size.m_fX = (float)childElement->IntAttribute("width"); 
	FontAtlas.v2Size.m_fY = (float)childElement->IntAttribute("height");
	FontAtlas.fKerning = (float)childElement->IntAttribute("kerning");
	
	iSprite.LoadTexture(FontAtlas.sSheet.c_str());
	iSprite.m_uvScale = FontAtlas.v2Size;
	GLint uvAttrib = glGetAttribLocation(iSprite.m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);
	iSprite.matrix_location = glGetUniformLocation (iSprite.m_ShaderProgram, "matrix");

	for (childElement = currentNode->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		if(str.length() > 1)
		{
		
			if(str == "&amp")
			ch = '&';
			
			else if(str =="&apos")
				ch = '\'';
			
			else if(str ==	"&astr")
				ch = '*';
			
			else if(str ==	"&bar" )
				ch = '|';
			
			else if(str ==	"&bslsh")
				ch = '\\';
			
			else if(str ==	"&col" )
				ch = ':';
			
			else if(str ==	"&fslsh")
				ch = '/';
			
			else if(str ==	"&gt" )
				ch = '>';
			
			else if(str ==	"&lt" )
				ch = '<';
			
			else if(str ==	"&quest") 
				ch = '?';
			
			else if(str ==	"&quot" )
				ch = '\"';
			
			else if(str ==	"&under")
				ch = '_';


		}
		else
		{
			ch = str.at(0);
		}
		charMap[ch].Name = str;
		charMap[ch].x0 = childElement->IntAttribute("x");
		charMap[ch].y0 = childElement->IntAttribute("y");
		charMap[ch].width = childElement->IntAttribute("width");
		charMap[ch].height =childElement->IntAttribute("height");
		charMap[ch].x1 = charMap[ch].x0 + charMap[ch].width;	
		charMap[ch].y1 = charMap[ch].y0 + charMap[ch].height;
		charMap[ch].offset = childElement->IntAttribute("offset");
	}
	ch = ' ';
	charMap[ch].Name = " ";
	charMap[ch].x0 = 0;
	charMap[ch].y0 = 0;
	charMap[ch].width = 8;
	charMap[ch].height =8;
	charMap[ch].x1 = 0;	
	charMap[ch].y1 = 0;
	charMap[ch].offset = 0;
	ch = '\n';
	charMap[ch].Name = "&ret";
	charMap[ch].x0 = 0;
	charMap[ch].y0 = 0;
	charMap[ch].width = 0;
	charMap[ch].height =0;
	charMap[ch].x1 = 0;	
	charMap[ch].y1 = 0;
	charMap[ch].offset = 0;
}
void FontManager::DrawString(std::string str,Vector2 pos,float scale)
{
	//Call LoadString
	LoadString(str,pos,scale);
	//Set iSprite's Scale and Position
	iSprite.SetScale(scale);
	iSprite.SetPosition(pos.m_fX, pos.m_fY);
	//Make a Char called c
	Char c;
	float newPos = 0;
	//Make a for loop
	for(int i = 0; i < DrawList.size();i++)
	{
		c = DrawList[i];
		
		//If i isn't the first letter
 		if(i != 0)
		{
			//If c.Name is the & symbol
			if(c.Name == "&ret")
			{
				//Move text after the symbol down a line
				pos.m_fX -= 20;
				newPos = pos.m_fY-4;
			}
			//Or
			else
			{
				//Make newPos equal two
				newPos = iSprite.GetPosition().m_fX + //iSprite's x pos plus
				c.width/2 + //Half the char's width plus
				DrawList[i-1].width/2 +	//Half the previous char's width plus
				FontAtlas.fKerning; //FontAtlas' fkerning
			}
			//Set iSprite's Position
			iSprite.SetPosition(Vector3(newPos,pos.m_fY,0.f));
		}
		//Or i is the first letter
		else
		{
			//Set iSprite's Position
			iSprite.SetPosition(Vector3(pos.m_fX + c.width/2, pos.m_fY, 0.f));
		}

		//Set iSprite's UVs and Scale
		iSprite.m_minUVCoords = Vector2(c.x0,c.y0) ;
		iSprite.m_maxUVCoords = Vector2(c.x1,c.y1) ;
		iSprite.SetUVData();
		iSprite.SetScale(c.width*scale,c.height*scale);

		//Set iSprite's model matrix
		iSprite.modelMatrix->m_afArray[0]  = iSprite.GetScale().m_fX *iSprite.m_fZoom;
		iSprite.modelMatrix->m_afArray[5]  = iSprite.GetScale().m_fY *iSprite.m_fZoom;
		iSprite.modelMatrix->m_afArray[12] = iSprite.GetPosition().m_fX;
		iSprite.modelMatrix->m_afArray[13] = iSprite.GetPosition().m_fY  - (c.offset * iSprite.m_fZoom); //this is going to need to change for and use the offest variable from each char
		iSprite.modelMatrix->m_afArray[14] = iSprite.GetPosition().m_fZ;

		*iSprite.MVP =  (*Ortho * *iSprite.modelMatrix) ;
		iSprite.Quad::Draw();
	}
}
//Load text
void FontManager::LoadString(std::string str,Vector2 pos,float scale)
{
	DrawList.clear();
	char c;
	for(CharCount = 0; CharCount < str.length();CharCount++)
	{
		c = str.at(CharCount);
		DrawList.push_back(charMap[c]);

	}
}