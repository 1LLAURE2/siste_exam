#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


void Menu_alumno();
void Menu_Docente();
void Menu_admin();
	
int Ingreso_Curso(int n,struct curso c);	
void Imprimir_cursos_totales(int n,struct curso c);

int Ingresar_Alumno(int n,struct alumno a);
void Imprimir_alumnos_totales(struct alumno a);

void Asignar_Cuso_Docente(struct docente d, struct curso c,int cod_curso,int cod_docente, struct det_doc_cur de);


int Ingreso_docente(int n,struct docente d);
void Imprimir_docentes_totales(struct docente d);

//int Ingreso_pregunta(int n,struct pregunta p, struct alternativa a);

////////////////////int Ingreso_pregunta(int n,struct pregunta p, struct alternativa a, int id_curso);
int Ingreso_pregunta_literatura(int n,struct pregunta p, struct alternativa a, int id_curso);
int Ingreso_pregunta_historia(int n,struct pregunta p, struct alternativa a, int id_curso);


//void Imprimir_preguntas_alternativas(struct pregunta p, struct alternativa a);
////////////////////void Imprimir_preguntas_alternativas(struct pregunta p, struct alternativa a,int id_curso);
void Imprimir_preguntas_alternat_historia(struct pregunta p, struct alternativa a,int id_curso);
void Imprimir_preguntas_alternat_literatura(struct pregunta p, struct alternativa a,int id_curso);

bool Verificar_CursoxCodigo(struct curso c, int cod);
bool Verificar_DocentexCodigo(struct docente d, int cod);


void Imprimir_docente_curso(struct det_doc_cur de,struct curso c,struct docente d);


void Examen_Aleatorio_Historia(struct pregunta p, struct alternativa a,struct evaluacion e, int cod_curso, int n_aleatorio,int id_pregunta, int *nota);


struct det_alu_cur{
	int det_cur_cod;
	int det_alu_cod;
};

struct det_doc_cur{
	int det_doc_cod;
	int det_cur_cod;
};

struct curso{
	int  cur_cod;		//codigo de curso
	char cur_des[35];	//descripcion del curso
	int  cur_est;		//estado del curso;
};

struct evaluacion{
	int  cal_cod;		//codigo correlativo de la calificacion
	char cal_alu_cod;	//codigo de alumno evaluado
	char cal_cur_cod;	//codigo del curso
	int  cal_not;		//nota de la evaluacion
	
	int  cal_cod_pre;
	char cal_res[30];
};


struct alternativa{
	int  alt_pre_cod;	//codigo de pregunta
	char alt_opc;	//opcion a-b-c-d
	char alt_res[30];	//respuesta de la pregunta
	int  alt_est;		//estado de la alternativa 1-si es correcto y 2 si es incorrecto
	
	
	int alt_cod_cur;
};

struct pregunta{
	int  pre_cur_cod;   //DEPENDE DEL CODIGO DEL CURSO
	
	int  pre_cod;		//codigo de la pregunta
	char pre_des[300];	//pregunta
	int  pre_est;		//estado de la pregunta
};

struct alumno{
	int  alu_cod;		//codigo de alumno
	char alu_nom[35];	//nombres del alumno
	char alu_ape[35];	//apellido del alumno
};

struct docente{
	int  doc_cod;		//codigo de docente
	char doc_nom[35];	//nombre de docente
	char doc_ape[35];	//apellido de docente
	int  doc_est;		//estado del docente
};



int main(int argc, char *argv[]) {
	
	//srand(time(NULL));
	
	int opc;
	bool ini=true;
	
	do{
		system("CLS");
		cout<<"*************************"<<endl;
		cout<<"****** SISTEMA UPN ******"<<endl;
		cout<<"*************************"<<endl;
		cout<<"[1]. LOGIN ALUMNO "<<endl;
		cout<<"[2]. LOGIN DOCENTE"<<endl;
		cout<<"[3]. SALIR"<<endl;
		cin>>opc;
		switch(opc)
		{
		case 1:
			Menu_alumno();
			break;
		case 2:
			Menu_Docente();
			break;
		case 3:
			ini=false;
			break;
		case 70164214:           //INGRESO A ADMINISTRADOR
			Menu_admin();
			break;
		default:
			cout<<"OPCION INVALIDA"<<endl;
		}
	} while(ini==true);
}

void Menu_Docente()
{
	
	int n_preg=0;
	
	struct pregunta pre;
	struct alternativa alt;

	bool band_menu_login=true;
	int opc;
	do{
		system("CLS");
		cout<<"***************************"<<endl;
		cout<<"****BIENVENIDO DOCENTE****"<<endl;
		cout<<"***************************"<<endl;
		cout<<"[1]. REGISTRAR PREGUNTAS DE HISTORIA  "<<endl;
		cout<<"[2]. REGISTRAR PREGUNTAS DE LITERATURA"<<endl;
		cout<<"[3]. MOSTRAR PREGUNTAS HISTORIA Y ALTERNATIVAS   "<<endl;
		cout<<"[4]. MOSTRAR PREGUNTAS LIERATURA Y ALTERNATIVAS   "<<endl;
		cout<<"[5]. SALIR             "<<endl;
		cin>>opc;
		switch(opc)
		{
		case 1:
			//n_preg=Ingreso_pregunta(n_preg,pre,alt,1);
			n_preg=Ingreso_pregunta_historia(n_preg,pre,alt,1);
			system("PAUSE");
			break;
		case 2:
			//n_preg=Ingreso_pregunta(n_preg,pre,alt,2);
			n_preg=Ingreso_pregunta_literatura(n_preg,pre,alt,2);
			system("PAUSE");
			break;
		case 3:
			//Imprimir_preguntas_alternativas(pre, alt,1);
			Imprimir_preguntas_alternat_historia(pre, alt,1);
			system("PAUSE");
			break;
		case 4:
			//Imprimir_preguntas_alternativas(pre, alt,2);//2
			Imprimir_preguntas_alternat_literatura(pre, alt,2);
			system("PAUSE");
			break;
		case 5:
			band_menu_login=false;
			break;
		default:
			cout<<"OPCION INVALIDA"<<endl;
		}
	} while(band_menu_login==true);
}

void Menu_alumno()
{
	
	struct pregunta pre;
	struct alternativa alt;
	struct evaluacion eva;
	
	srand(time(NULL));
	
	int aleatorio;		//NUMEROS ENTRE 1 Y 25;
	
	int nota=0;
	
	int opc;
	bool band_menu_alum=true;
	do{
		system("CLS");
		cout<<"*****************************"<<endl;
		cout<<"******BIENVENIDO ALUMNO******"<<endl;
		cout<<"*****************************"<<endl;
		cout<<"[1]. RENDIR EXAMEN POR CURSO HISTORIA "<<endl; 	//GENERO EXAMEN ALEATORIO
		cout<<"[2]. VISUALIZAR RESULTADO     "<<endl;
		cout<<"[3]. VISUALIZAR CURSOS     "<<endl;
		cout<<"[4]. SALIR             "<<endl;
		cin>>opc;
		switch(opc)
		{
		case 1:
			system("cls");
			for (int i=1;i<6;i++)
			{
				aleatorio=1+rand()%(25-1);
				Examen_Aleatorio_Historia(pre, alt,eva, 1, aleatorio,i, &nota);
			}
			cout<<"USTED OBTUBO UNA NOTA DE "<<nota<<endl;
			
			nota=0;	//una vez que responsa le asiganmos cero nuevamente
			system("PAUSE");
			cout<<"SU NOTA ES: "<<nota;
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			band_menu_alum=false;
			break;
		default:
			cout<<"OPCION INVALIDA"<<endl;
		}
	} while(band_menu_alum==true);
}

void Menu_admin()
{
	
	struct curso cur;
	struct alumno alu;
	struct docente doc;
	struct det_doc_cur curXdoc;
		int n_curso=0;
	int n_alumno=0;
	int n_docente=0;

	int cod_docente;
	int cod_curso;
	
	int opc;
	bool band_menu_admin=true;
	do{
		system("CLS");
		cout<<"*****************************"<<endl;
		cout<<"****** BIENVENIDO ADMIN******"<<endl;
		cout<<"*****************************"<<endl;
		cout<<"[1]. REGISTAR ALUMNO   "<<endl;
		cout<<"[2]. REGISTRAR CURSO     "<<endl;					//LISTO
		cout<<"[3]. VISUALIZAR CURSOS     "<<endl;
		cout<<"[4]. VISUALIZAR ALUMNOS            "<<endl;
		cout<<"[5]. ASIGNAR CURSO A DOCENTE            "<<endl;
		cout<<"[6]. REGISTAR DOCENTE   "<<endl;
		cout<<"[7]. VISUALIZAR  DOCENTE   "<<endl;
		cout<<"[8]. SALIR             "<<endl;
		cout<<"[9]. VISUALIZAR DOCENTE POR CURSOS ASIGANDOS  "<<endl;
		cin>>opc;
		switch(opc)
		{
		case 1:
			n_alumno=Ingresar_Alumno(n_alumno,alu);
			break;
		case 2:
				n_curso=Ingreso_Curso(n_curso,cur);
			break;
		case 3:
			Imprimir_cursos_totales(n_curso,cur);
			system("pause");
			break;
		case 4:
			Imprimir_alumnos_totales(alu);
			system("PAUSE");
			break;
		case 5:
			system("CLS");
			cout<<"BUSCAR DOCENTE POR CODIGO"<<"\t";
			cin>>cod_docente;
			if(Verificar_DocentexCodigo(doc,cod_docente)==true){
				cout<<"DIGITE EL CODIGO DEL CURSO A ASIGNAR "<<"\t";
				cin>>cod_curso;
				if(Verificar_CursoxCodigo(cur,cod_curso)==true)
				{
					Asignar_Cuso_Docente(doc, cur,cod_curso,cod_docente,curXdoc);   
					cout<<"SE ASIGNO CORRECTAMENTE"<<endl;
					
				}else{
					cout<<"NO SE ENCONTRO EL REGISTRO"<<endl;
				}
			}
			else{
				cout<<"NO SE ENCONTRO EL REGISTRO"<<endl;
			}
			system("PAUSE");
			break;
		case 6:
			n_docente=Ingreso_docente(n_docente,doc);
			system("PAUSE");
			break;
		case 7:
			Imprimir_docentes_totales(doc);
			system("PAUSE");
			break;
		case 8:		//SALIR
			band_menu_admin=false;
			break;
		case 9:
			
			Imprimir_docente_curso(curXdoc,cur,doc);
			system("PAUSE");
			break;
		default:
			cout<<"OPCION INVALIDA"<<endl;
		}
	} while(band_menu_admin==true);
}

int Ingreso_Curso(int n,struct curso c){			//OK
	FILE *arc_curso;
	arc_curso=fopen("D:\\T4\\curso.txt","a+t");
	
	if(arc_curso!=NULL)
	{
		cout<<"INGRESE CODIGO          "<<"\t";
		cin>>c.cur_cod;
		cout<<"INGRESE NOMBRE DEL CURSO"<<"\t";
		cin.ignore();
		cin.getline(c.cur_des,35);
		c.cur_est=1;
		fwrite(&c,sizeof(curso),1,arc_curso);
		fclose(arc_curso);
		return n;
	}
	else{
		cout<<"ARCHIVO NO CREADO "<<endl;
		exit(1);
	}
}

void Imprimir_cursos_totales(int n,struct curso c)  //OK
{
	FILE *lec_curso;
	lec_curso=fopen("D:\\T4\\curso.txt","rt");
	if(lec_curso!=NULL)
	{
			fread(&c,sizeof(curso),1,lec_curso);
			cout<<"###REPORTE DE CURSOS###"<<endl;
			cout<<"CODIGO "<<"\t"<<"CURSO "<<endl;
			do{
				cout<<c.cur_cod<<"\t"<<c.cur_des<<endl;
				fread(&c,sizeof(curso),1,lec_curso);
			} while(!feof(lec_curso));
	}
	else
	{
		cout<<"	ARCHIVO NO ENCONTRADO"<<endl;
		exit(1);
	}
}

int Ingresar_Alumno(int n,struct alumno a)			//OK
{
	FILE *arc_alumno;
	arc_alumno=fopen("D:\\T4\\alumno.txt","a+t");
	
	if(arc_alumno!=NULL)
	{
		cout<<" INGRESO DE ALUMNO"<<endl;
		
		cout<<"INGRESE CODIGO          "<<"\t";
		cin>>a.alu_cod;
		cout<<"INGRESE NOMBRES         "<<"\t";
		cin.ignore();
		cin.getline(a.alu_nom,35);
		cout<<"INGRESE APELLIDOS       "<<"\t";
		//cin.ignore();
		cin.getline(a.alu_ape,35);
		
		fwrite(&a,sizeof(alumno),1,arc_alumno);
		fclose(arc_alumno);
		return n;
	}
	else{
		cout<<"ARCHIVO NO CREADO "<<endl;
		exit(1);
	}
}

void Imprimir_alumnos_totales(struct alumno a)		//OK
{
	FILE *lec_alumno;
	lec_alumno=fopen("D:\\T4\\alumno.txt","rt");
	if(lec_alumno!=NULL)
	{
		fread(&a,sizeof(alumno),1,lec_alumno);
		cout<<"###REPORTE DE ALUMNOS###"<<endl;
		cout<<"CODIGO"<<"\t"<<"   NOMBRES"<<"\t"<<"\t"<<"APELLDOS"<<endl;
		do{
			
			cout<<a.alu_cod<<"\t"<<a.alu_nom<<"\t"<<"\t"<<a.alu_ape<<endl;	
			fread(&a,sizeof(alumno),1,lec_alumno);
		} while(!feof(lec_alumno));
	}
	else{
		cout<<"ARCHIVO NO ENCONTRADO "<<endl;
		exit(1);
	}
}

void Asignar_Cuso_Docente(struct docente d, struct curso c,int cod_curso,int cod_docente, struct det_doc_cur de)    //REVISAR
{
	bool ban_doce=false;
	bool ban_curs=false;
	
	FILE *arc_docente;
	arc_docente=fopen("D:\\T4\\docente.txt","rt");
	FILE *arc_curso;
	arc_curso=fopen("D:\\T4\\curso.txt","rt");
	
	FILE *arc_doce_curso;
	arc_doce_curso=fopen("D:\\T4\\detalle_docente_curso.txt","a+t");
	
	if(arc_curso==NULL){
		cout<<"NO SE REGISTRARON CURSOS HASTA EL MOMENTO"<<endl;
		exit(1);
	}
	if(arc_docente==NULL)
	{
		cout<<"NO SE REGISTRARON DOCENTES HASTA EL MOMENTO"<<endl;
		exit(1);
	}
	else{
		
		cout<<"++++++++++++++++++++++++"<<endl;
		cout<<"ASIGNAR CURSO A DOCENTE"<<endl;
		cout<<"++++++++++++++++++++++++"<<endl;
		do{
			
			
			
			fread(&d,sizeof(docente),1,arc_docente);
			do{
				
				if(cod_docente==d.doc_cod){
					ban_doce=true;
					cout<<"DOCENTE:  "<<"\t"<<d.doc_nom<<"\t"<<d.doc_ape<<endl;
				}
				fread(&d,sizeof(docente),1,arc_docente);
			} while(!feof(arc_docente));
			
		} while(ban_doce==false);
		fclose(arc_docente);
		do{
			
			
			
			fread(&c,sizeof(curso),1,arc_curso);
			do{
				if(cod_curso==c.cur_cod)
				{
					ban_curs=true;
					cout<<"CURSO:  "<<"\t"<<c.cur_des<<endl;
				}
				fread(&c,sizeof(curso),1,arc_curso);
			} while(!feof(arc_curso));
			
			fclose(arc_curso);
			
		} while(ban_curs==false);
	
		if(ban_curs==true and ban_doce==true)
		{
			de.det_doc_cod=cod_docente;
			de.det_cur_cod=cod_curso;
			fwrite(&de,sizeof(det_doc_cur),1,arc_doce_curso);
			fclose(arc_doce_curso);
		}
		fclose(arc_doce_curso);
		
	}
}
int Ingreso_docente(int n,struct docente d)		     						 //OK
{
	FILE *arc_docente;
	arc_docente=fopen("D:\\T4\\docente.txt","a+t");
	if(arc_docente!=NULL)
	{
		
		cout<<"INGRESE CODIGO  "<<"\t";
		cin>>d.doc_cod;
		cout<<"INGRESE NOMBRES "<<"\t";
		cin.ignore();
		cin.getline(d.doc_nom,35);
		cout<<"INGRESE APELLIDOS "<<"\t";
		//cin.ignore();
		cin.getline(d.doc_ape,35);
		d.doc_est=1;
		fwrite(&d,sizeof(docente),1,arc_docente);
		n=n+1;
		fclose(arc_docente);
	}
	else{
		cout<<"NO SE ENCONTRO EL ARCHIVO"<<endl;
		exit(1);
	}
	return n;
}

void Imprimir_docentes_totales(struct docente d)							 //OK
{
	FILE *lec_docente;
	lec_docente=fopen("D:\\T4\\docente.txt","rt");
	if(lec_docente!=NULL)
	{
		cout<<"CODIGO"<<"\t"<<"NOMBRES"<<"\t"<<"\t"<<"APELLIDOS"<<endl;
		fread(&d,sizeof(docente),1,lec_docente);
		do{
			cout<<d.doc_cod<<"\t"<<d.doc_nom<<"\t"<<"\t"<<d.doc_ape<<endl;
			fread(&d,sizeof(docente),1,lec_docente);
		} while(!feof(lec_docente));
	}
	else{
		cout<<"ERROR AL ABRIR EL ARCHIVO"<<endl;
		exit(1);
	}
}

int Ingreso_pregunta_historia(int n,struct pregunta p, struct alternativa a, int id_curso)			  //OK
{
	
	FILE *arc_pregunta;
	arc_pregunta=fopen("D:\\T4\\pre_historia.txt","a+t");
	
	FILE *arc_respuesta;
	arc_respuesta=fopen("D:\\T4\\alt_historia.txt","a+t");
	
	if(arc_pregunta!=NULL){
		
		if(arc_respuesta!=NULL)
		{
			p.pre_cur_cod=id_curso;
			cout<<"INGRESE CODIGO DE PREGUNTA"<<"\t";
			cin>>p.pre_cod;
			cout<<"INGRESE LA PREGUNTA       "<<"\t";
			cin.ignore();
			cin.getline(p.pre_des,300);
			p.pre_est=1;
			fwrite(&p,sizeof(pregunta),1,arc_pregunta);
			for(int i=0;i<4;i++){
				a.alt_pre_cod=p.pre_cod;
				a.alt_opc =char(65+i);
				cout<<"INGRESE LA ALTERNATIVA "<<char(65+i)<<"\t";
				//cin.ignore();
				cin.getline(a.alt_res,30);
				cout<<"1:CORRECTO /2: INCORRECTO             "<<"\t";
				cin>>a.alt_est;
				
				a.alt_cod_cur=id_curso;
				
				fwrite(&a,sizeof(alternativa),1,arc_respuesta);
				n=n+1;
				
				cin.ignore();
			}
			fclose(arc_pregunta);
			fclose(arc_respuesta);
		}
		else{
			cout<<"NO SE PUDO ENCONTRAR EL ARCHIVO"<<endl;
			exit(1);
		}
	}
	else{
		cout<<"ARCHIVO NO UBICADO"<<endl;
		exit(1);
	}
	return n;
}

void Imprimir_preguntas_alternat_historia(struct pregunta p, struct alternativa a,int id_curso) //OK 
{
	FILE *lec_pregunta;
	lec_pregunta=fopen("D:\\T4\\pre_historia.txt","rt");
	
	FILE *lec_respuesta;

	if(lec_pregunta==NULL)
	{
		cout<<"NO SE PUDO ENCONTRAR EL ARCHIVO"<<endl;
		exit(1);
	}
	fread(&p,sizeof(pregunta),1,lec_pregunta);
	cout<<"CODIDO"<<"\t"<<"                PREGUNTA             "<<endl;
	do{
		
		if(p.pre_cur_cod==id_curso){
			cout<<p.pre_cod<<"\t"<<p.pre_des<<endl;
			
			lec_respuesta=fopen("D:\\T4\\alt_historia.txt","rt");
			fread(&a,sizeof(alternativa),1,lec_respuesta);
			cout<<"ALTERNATIVA "<<"RESPUESTA"<<endl;
			do{
				if(p.pre_cod==a.alt_pre_cod and a.alt_cod_cur==id_curso){
					cout<<a.alt_opc<<"\t"<<a.alt_res<<endl;
				}
				fread(&a,sizeof(alternativa),1,lec_respuesta);
			} while(!feof(lec_respuesta));
			fclose(lec_respuesta);
		}
		
		fread(&p,sizeof(pregunta),1,lec_pregunta);
	} while(!feof(lec_pregunta));
	fclose(lec_pregunta);
}


bool Verificar_CursoxCodigo(struct curso c, int cod)
{
	bool ban=false;
	FILE *arc_curso;
	arc_curso=fopen("D:\\T4\\curso.txt","rt");
	if(arc_curso==NULL)
	{
		cout<<"NO EXISTEN DATOS REGISTRADOS"<<endl;
		//return ban;
		exit(1);
	}
	else{
		fread(&c,sizeof(curso),1,arc_curso);
		do{
			if(c.cur_cod==cod)
			{
				ban=true;
			}
			fread(&c,sizeof(curso),1,arc_curso);
		} while(!feof(arc_curso));
		fclose(arc_curso);
	}
	return ban;
}

bool Verificar_DocentexCodigo(struct docente d, int cod)
{
	bool ban=false;
	FILE *arc_docente;
	arc_docente=fopen("D:\\T4\\docente.txt","rt");
	if(arc_docente==NULL)
	{
		cout<<"NO EXISTEN DATOS REGISTRADOS"<<endl;
		exit(1);
	}
	else{
		fread(&d,sizeof(docente),1,arc_docente);
		do{
			if(d.doc_cod==cod)
			{
				ban=true;
			}
			fread(&d,sizeof(docente),1,arc_docente);
		} while(!feof(arc_docente));
		fclose(arc_docente);
	}
	return ban;
}

void Imprimir_docente_curso(struct det_doc_cur de,struct curso c,struct docente d)
{
	FILE *arc_detCur_Doc;
	arc_detCur_Doc=fopen("D:\\T4\\detalle_docente_curso.txt","rt");
	FILE *arc_curso;
	FILE *arc_docente;
	
	if(arc_detCur_Doc!=NULL)
	{
		cout<<"*************************************"<<endl;
		cout<<"**** CURSOS POR DOCENTE ASIGANDO ****"<<endl;
		cout<<"*************************************"<<endl;
		
		fread(&de,sizeof(det_doc_cur),1,arc_detCur_Doc);
		cout<<"  CURSO"<<"\t"<<"                DOCENTE                   "<<endl;
		do{
		
			//cout<<de.det_cur_cod<<"\t"<<"\t"<<de.det_doc_cod<<endl;
			
			
			arc_curso=fopen("D:\\T4\\curso.txt","rt");
			arc_docente=fopen("D:\\T4\\docente.txt","rt");
			
			fread(&c,sizeof(curso),1,arc_curso);
			fread(&d,sizeof(docente),1,arc_docente);
			do{
				
				if(de.det_cur_cod==c.cur_cod and de.det_doc_cod==d.doc_cod)
				{
					cout<<c.cur_des<<"\t"<<d.doc_nom<<", "<<d.doc_ape<<endl;
				}
//				if(de.det_doc_cod==d.doc_cod)
//				{
//					cout<<d.doc_nom<<", "<<d.doc_ape<<endl;
//				}
				
				fread(&d,sizeof(docente),1,arc_docente);
				fread(&c,sizeof(curso),1,arc_curso);
				
			} while(!feof(arc_curso) || !feof(arc_docente));
			
			fclose(arc_curso);
			fclose(arc_docente);
//		
			fread(&de,sizeof(det_doc_cur),1,arc_detCur_Doc);
		} while(!feof(arc_detCur_Doc));
		fclose(arc_detCur_Doc);
	}
	else{
		cout<<"NO EXISTEN ASIGNACIONES DE CURSO"<<endl;
	}
}




int Ingreso_pregunta_literatura(int n,struct pregunta p, struct alternativa a, int id_curso)			  //OK
{
	
	FILE *arc_pregunta;
	arc_pregunta=fopen("D:\\T4\\pre_literatura.txt","a+t");
	
	FILE *arc_respuesta;
	arc_respuesta=fopen("D:\\T4\\alt_literatura.txt","a+t");
	
	if(arc_pregunta!=NULL){
		
		if(arc_respuesta!=NULL)
		{
			p.pre_cur_cod=id_curso;
			cout<<"INGRESE CODIGO DE PREGUNTA"<<"\t";
			cin>>p.pre_cod;
			cout<<"INGRESE LA PREGUNTA       "<<"\t";
			cin.ignore();
			cin.getline(p.pre_des,300);
			p.pre_est=1;
			fwrite(&p,sizeof(pregunta),1,arc_pregunta);
			for(int i=0;i<4;i++){
				a.alt_pre_cod=p.pre_cod;
				a.alt_opc =char(65+i);
				cout<<"INGRESE LA ALTERNATIVA "<<char(65+i)<<"\t";
				//cin.ignore();
				cin.getline(a.alt_res,30);
				cout<<"1:CORRECTO /2: INCORRECTO             "<<"\t";
				cin>>a.alt_est;
				
				a.alt_cod_cur=id_curso;
				
				fwrite(&a,sizeof(alternativa),1,arc_respuesta);
				n=n+1;
				
				cin.ignore();
			}
			fclose(arc_pregunta);
			fclose(arc_respuesta);
		}
		else{
			cout<<"NO SE PUDO ENCONTRAR EL ARCHIVO"<<endl;
			exit(1);
		}
	}
	else{
		cout<<"ARCHIVO NO UBICADO"<<endl;
		exit(1);
	}
	return n;
}

void Imprimir_preguntas_alternat_literatura(struct pregunta p, struct alternativa a,int id_curso) //OK 
{
	FILE *lec_pregunta;
	lec_pregunta=fopen("D:\\T4\\pre_literatura.txt","rt");
	
	FILE *lec_respuesta;
	
	if(lec_pregunta==NULL)
	{
		cout<<"NO SE PUDO ENCONTRAR EL ARCHIVO"<<endl;
		exit(1);
	}
	fread(&p,sizeof(pregunta),1,lec_pregunta);
	cout<<"CODIDO"<<"\t"<<"                PREGUNTA             "<<endl;
	do{
		
		if(p.pre_cur_cod==id_curso){
			cout<<p.pre_cod<<"\t"<<p.pre_des<<endl;
			
			lec_respuesta=fopen("D:\\T4\\alt_literatura.txt","rt");
			fread(&a,sizeof(alternativa),1,lec_respuesta);
			cout<<"ALTERNATIVA "<<"RESPUESTA"<<endl;
			do{
				if(p.pre_cod==a.alt_pre_cod and a.alt_cod_cur==id_curso){
					cout<<a.alt_opc<<"\t"<<a.alt_res<<endl;
				}
				fread(&a,sizeof(alternativa),1,lec_respuesta);
			} while(!feof(lec_respuesta));
			fclose(lec_respuesta);
		}
		
		fread(&p,sizeof(pregunta),1,lec_pregunta);
	} while(!feof(lec_pregunta));
	fclose(lec_pregunta);
}

void Examen_Aleatorio_Historia(struct pregunta p, struct alternativa a,struct evaluacion e, int cod_curso, int n_aleatorio,int id_pregunta, int *nota)
{
	struct pregunta pp;
	//struct alternativa al;
	char correcta[30];
	char respuesta[30];
	//char opcion;
	
	FILE *arc_pre_historia;
	arc_pre_historia=fopen("D:\\T4\\pre_historia.txt","rt");
	
	FILE *arc_alt_historia;
	
	FILE *gen_pre_historia;
	gen_pre_historia=fopen("D:\\T4\\examen_Generado.txt","a+t");
	
	
	if(arc_pre_historia!=NULL)
	{
		
		fread(&p,sizeof(pregunta),1,arc_pre_historia);
		cout<<" N°"<<"                     PREGUNTA                      "<<endl;
		do{
			
			arc_alt_historia=fopen("D:\\T4\\alt_historia.txt","rt");
			if(p.pre_cod==n_aleatorio and p.pre_est==1 and p.pre_cur_cod==cod_curso){
				
				cout<<id_pregunta<<".-  "<<p.pre_des<<endl;
					
				fread(&a,sizeof(alternativa),1,arc_alt_historia);
				cout<<"OPCION "<<"\tRESPUESTAS"<<endl;
				do{
					//if((p.pre_cod==n_aleatorio and p.pre_est==1) and (al.alt_pre_cod==n_aleatorio and al.alt_est==1)){
					if(a.alt_pre_cod==p.pre_cod){
						cout<<a.alt_opc<<").  "<<a.alt_res<<endl;
						if(a.alt_est==1){
							strcpy(correcta,a.alt_res);
						}
					}
					
					fread(&a,sizeof(alternativa),1,arc_alt_historia);
				} while(!feof(arc_alt_historia));
				fclose(arc_alt_historia);
				fflush(stdin);
				//cin.ignore();
				cout<<"INGRESE SU RESPUESTA"<<endl;
				cin.getline(respuesta,30);
				
				//if(strcmp(a.alt_opc,respuesta)==0 || strcmp(al.alt_res,respuesta)==0)
				if( strcmp(correcta,respuesta)==0 )
				{
					cout<<"RESPUESTA CORRECTA"<<endl;
					*nota=*nota+4;     //generare 5 pregntas asi que seria 20 puntos
					cout<<"TIENE "<<*nota<<"  PUNTOS"<<endl;
				}
				else{
					cout<<"RESPUESTA INCORRECTA"<<" ERA "<<correcta<<" USTED ESCRIBIO "<<respuesta<<endl;
				}
				
				
				pp.pre_cur_cod=cod_curso;   //1-historia
				pp.pre_cod=id_pregunta; 	//id lo voy a colocar con for
				strcpy(pp.pre_des,p.pre_des);		//contenido de la pregunta
				
				fwrite(&pp,sizeof(pregunta),1,gen_pre_historia);
				p.pre_est=2;			    	//cambio el estado de la pregunta-asi no volvera a repetir
			}
			
			fread(&p,sizeof(pregunta),1,arc_pre_historia);
			
		} while(!feof(arc_pre_historia));
		fclose(arc_pre_historia);
	}
	else
	   {
		cout<<"AUN NO ADICIONADO PREGUNTAS DEL CURSO"<<endl;
		Menu_admin();
	}
	
	
	
}
