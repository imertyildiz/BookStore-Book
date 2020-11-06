#include "SoftCopy.h"
/* YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. DO NOT MODIFY THE HEADER FILE AS IT WILL BE
REPLACED BY THE ORIGINAL HEADER DURING TESTING. THE REQUIRED
HEADER FILE IS ALREADY INCLUDED FOR YOU ABOVE THIS COMMENT BLOCK.
THE CONSTRUCTOR and DESTRUCTOR ARE ALREADY IMPLEMENTED.
START YOUR IMPLEMENTATIONS BELOW THOSE. */


// DONE
SoftCopy::SoftCopy(int ISBN, double price, int startPage, int endPage) : Book(ISBN, price) {
	this->startPage = startPage;
	this->endPage = endPage;
	this->numberOfPages = (endPage - startPage) + 1;
	this->firstHalf = NULL;
	this->secondHalf = NULL;
	this->pageContent = "";
}

// DONE
SoftCopy::~SoftCopy() {
	if (firstHalf != NULL)
		delete firstHalf;
	if (secondHalf != NULL)
		delete secondHalf;
}
SoftCopy::SoftCopy(const SoftCopy& rhs){
	this->startPage=rhs.startPage;
	this->endPage=rhs.endPage;
	this->numberOfPages=rhs.numberOfPages;
	this->pageContent=rhs.pageContent.c_str();
	this->price=rhs.price;
	this->ISBN=rhs.ISBN;
	this->next=rhs.next;
	SoftCopy* aa;
	SoftCopy* bb;
	if(rhs.firstHalf){
		aa= new SoftCopy(*(rhs.firstHalf));
	}
	else{
		aa=NULL;
	}
	if(rhs.secondHalf){
		bb= new SoftCopy(*(rhs.secondHalf));
	}
	else{
		bb=NULL;
	}
	this->firstHalf=aa;
	this->secondHalf=bb;
	
	
}
SoftCopy& SoftCopy::operator=(const SoftCopy& rhs){
	if(this->firstHalf){
		delete firstHalf;
	}
	if(this->secondHalf){
		delete secondHalf;
	}

	this->startPage=rhs.startPage;
	this->endPage=rhs.endPage;
	this->numberOfPages=rhs.numberOfPages;
	this->pageContent=rhs.pageContent.c_str();
	this->price=rhs.price;
	this->ISBN=rhs.ISBN;
	this->next=rhs.next;
	SoftCopy* aa;
	SoftCopy* bb;
	if(rhs.firstHalf){
		aa= new SoftCopy(*(rhs.firstHalf));
	}
	else{
		aa=NULL;
	}
	if(rhs.secondHalf){
		bb= new SoftCopy(*(rhs.secondHalf));
	}
	else{
		bb=NULL;
	}
	this->firstHalf=aa;
	this->secondHalf=bb;
	return *this;
}
SoftCopy& SoftCopy::operator+(const SoftCopy& rhs) const{
	//Bir tek bu kaldı
	SoftCopy * last= new SoftCopy(*this);
	for(int i=rhs.startPage;i<(rhs.endPage+1);i++){
		SoftCopy* tmp= (SoftCopy*)&rhs;
		int st=tmp->startPage;
		int en=tmp->endPage;
		if(st==en){
			//FOUND
			last->UploadPage(tmp->pageContent,st);
			continue;
		}
		while(1){
			int deg=tmp->startPage+(tmp->numberOfPages-1)/2;
			if(i<=deg){
				//Left
				if(st==en){
					// FOUND
					last->UploadPage(tmp->pageContent,st);
					break;
				}
				else{
					en=deg;
					if(tmp->firstHalf){
						//First Half Null DEGIL
						tmp=tmp->firstHalf;
					}
					else{
						//First half NULL !!
						break;
					}
				}
			}
			else if(i > deg){
				//Rİght

				if(st==en){
					// FOUND
					last->UploadPage(tmp->pageContent,st);
					break;
				}
				else{
					st=deg+1;
					if(tmp->secondHalf){
						//Second Half Null DEGIL
						tmp=tmp->secondHalf;
					}
					else{
						//Second Half NULL !! do nothing.
						break;
					}
				}
			}
		}
		
	}
	return *last;
}
Book* SoftCopy::Clone() const{
	SoftCopy* x= new SoftCopy(*this);
	return x;
}

void SoftCopy::Discount(){
	this->price=price*(0.75);
	if(this->firstHalf){
		this->firstHalf->Discount();
	}
	if(this->secondHalf){
		this->secondHalf->Discount();
	}
}

void SoftCopy::UploadPage(string String, int Page){
	SoftCopy* tmp= (SoftCopy*)this;
	int st=tmp->startPage;
	int en= tmp->endPage;
	int deg=tmp->startPage+(tmp->numberOfPages-1)/2;
	if(Page<=deg){
		//Left
		if(st==en){
			this->pageContent.append(String);
		}
		else{
			en=deg;
			if(tmp->firstHalf){
			//First Half Null DEGIL
			tmp->firstHalf->UploadPage(String , Page);
			}
			else{
				//First half NULL !!
				tmp->firstHalf= new SoftCopy(tmp->ISBN,tmp->price,st,en);
				tmp->firstHalf->UploadPage(String , Page);
			}
		}
	}
	else if(Page > deg){
		//Rİght
		
		if(st==en){
			this->pageContent.append(String);
		}
		else{
			st=deg+1;
			if(tmp->secondHalf){
				//Second Half Null DEGIL
				tmp->secondHalf->UploadPage(String,Page);
			}
			else{
				//Second Half NULL !!
				tmp->secondHalf= new SoftCopy(tmp->ISBN,tmp->price,st,en);
				tmp->secondHalf->UploadPage(String , Page);
			}
		}
	}
}

string SoftCopy::Display(int from, int to) const{
	string out;
	for(int i=from;i<(to+1);i++){
		SoftCopy* tmp= (SoftCopy*)this;
		int st=tmp->startPage;
		int en=tmp->endPage;
		if(st==en){
			//FOUND
			out.append(tmp->pageContent);
			out.append("\n");
			continue;
		}
		while(1){
			int deg=tmp->startPage+(tmp->numberOfPages-1)/2;
			if(i<=deg){
				//Left
				if(st==en){
					// FOUND
					out.append(tmp->pageContent);
					out.append("\n");
					break;
				}
				else{
					en=deg;
					if(tmp->firstHalf){
						//First Half Null DEGIL
						tmp=tmp->firstHalf;
					}
					else{
						//First half NULL !!
						break;
					}
				}
			}
			else if(i > deg){
				//Rİght

				if(st==en){
					// FOUND
					out.append(tmp->pageContent);
					out.append("\n");
					break;
				}
				else{
					st=deg+1;
					if(tmp->secondHalf){
						//Second Half Null DEGIL
						tmp=tmp->secondHalf;
					}
					else{
						//Second Half NULL !! do nothing.
						break;
					}
				}
			}
		}
		
	}
	if (!out.empty()) {
		out.pop_back();
	}
	return out;
}


