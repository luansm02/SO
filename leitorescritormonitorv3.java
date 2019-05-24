import java.util.*;

public class leitorescritormonitorv3{
	
	static int qThread = 10; 						// numero de Threads (par)
	static int nEsc = 0;                            // contador de escritores
	static Produto p[] = new Produto[10];			// vetor de Elementos (Produtos) -inalterável
	static Escritor e[] = new Escritor[qThread/2];	// vetor de Escritores (metade da quantidade de threads)
	static Leitor l[] = new Leitor[qThread/2];		// vetor de leiores (metade da quantidade de threads)
	static Monitor mon = new Monitor();				// Insanciando monitor com seus metodos
	
	public static void main(String [] args){
		criacao();

		System.out.println("****LxE Versao sem Prioridade (MONITOR) (Leitura Suja)****\n");

		int cont=0;
		for(int i=0;i<qThread;i++){
			if(i%2==0){
				e[cont].start();
			}else{
				l[cont].start();
				cont++;
			}
		}
	}
	public static void criacao(){ // preenche valores dos produtos e insancia escritores e leitores
		p[0] = new Produto(1, "bolacha", 1.50);
		p[1] = new Produto(2, "sabao", 6.00);
		p[2] = new Produto(3, "leite", 4.50);
		p[3] = new Produto(4, "desodorante", 5.20);
		p[4] = new Produto(5, "detergente", 5.00);
		p[5] = new Produto(6, "talco", 3.50);
		p[6] = new Produto(7, "creme dental", 2.00);
		p[7] = new Produto(8, "feijao", 3.00);
		p[8] = new Produto(9, "arroz", 2.27);
		p[9] = new Produto(10, "suco", 1.00);

		for(int i=0;i<qThread/2;i++){
			e[i] = new Escritor();
			l[i] = new Leitor();
		}
	}

	public static class Leitor extends Thread{
		public void run(){
			int time = (int)(Math.random() * 3000+0);	// tempo de execução de um leitor

			System.out.println(Thread.currentThread().getName()+"-leitor Criada!");
			mon.leitura(time); // chama metodo do monitor
			System.out.println(Thread.currentThread().getName()+"-leitor Terminada!");
		}
	}

	public static class Escritor extends Thread{
		public void run(){
			double preco = Math.random()*10;			// novo preco
			int idProd = (int)(Math.random() * 10+0);	// id de produto aleatorio
			int time = (int)(Math.random() * 3000+0);	// tempo de execução de escritor
			
			synchronized(this){ //sincronização para incremento do contador de escritores
				nEsc++;
			}
			
			
			System.out.println(Thread.currentThread().getName()+"-escritor Criada!");
			mon.escrita(preco,idProd,time); // chama metodo do monitor
			System.out.println(Thread.currentThread().getName()+"-escritor Terminada!");
		}
	}

	public static class Monitor{
		
		//int qEsc = 0;
		
		public void leitura(int time){
			
			synchronized(this){ // sincronismo para verificacao de nEsc (Se nEsc>0, entao espera; caso contrario, executa)
				if(nEsc>0){
					System.out.println(Thread.currentThread().getName()+" BLOQUEADA! ");
					try{
						wait();
					}catch (Exception e) {
						System.out.println("Erro!");
					}
				}
			}
			
			System.out.println(Thread.currentThread().getName()+" LIVRE!");
			System.out.println("(leitura/Time:"+time+"ms)"+Thread.currentThread().getName()+" Emitindo Nota (...)****");
			try {
				Thread.sleep(time);	
			} catch (Exception e) {
				System.out.println("Erro!");
			}
			
			for(int i=0;i<10;i++){
				try {
					Thread.sleep(500);
					System.out.printf("	(Consulta "+Thread.currentThread().getName()+") Id:"+p[i].getId()+" Nome:"+p[i].getNome()+" Preco:%.2f\n",p[i].getPreco());
					
				} catch (Exception e) {
					System.out.println("Erro!");
				}
				
			}
		}
		public synchronized void escrita(double preco,int idProd,int time){
			
			//System.out.println(Thread.currentThread().getName()+" - qEsc: "+nEsc);
			System.out.println("(escritor/Time:"+time+"ms)"+Thread.currentThread().getName()+" Atualizando Preco do "+p[idProd].getNome()+" (...)****");
				
			try {
				Thread.sleep(time);	
			} catch (Exception e) {
				System.out.println("Erro!");
			}
				
			double precoAntigo = p[idProd].preco;
			p[idProd].setPreco(preco);
			System.out.printf("A "+Thread.currentThread().getName()+" atualizou o preco do "+p[idProd].getNome()+" de %.2f para %.2f\n",precoAntigo,p[idProd].getPreco());
				
			nEsc--;
			if(nEsc==0){ // se nEsc==0, entao notifica as thread leitoras
				try{
					notifyAll();System.out.println(Thread.currentThread().getName()+" NOTIFYALL!");
				} catch (Exception e) {
					System.out.println("Erro!");
				}
			}
			
		}
	}

	//CLASSE PRODUTO
	public static class Produto{
		int id;
		String nome;
		double preco;
		Produto(int id,String nome, double preco){
			this.id = id;
			this.nome = nome;
			this.preco = preco;
		}
		public int getId(){
			return this.id;
		}
		public String getNome(){
			return this.nome;
		}
		public double getPreco(){
			return this.preco;
		}
		public void setPreco(double newPreco){
			this.preco = newPreco;
		}
	}
}

//ok
