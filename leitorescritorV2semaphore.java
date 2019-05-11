import java.util.Scanner;

public class ProdutorConsumidor{
	
	static final int N=10;
	static escrita e = new escrita();
	static leitura l = new leitura();
	static our_monitor mon = new our_monitor();

	public static void main(String args[]){
		e.start();
		l.start();
	}

	static class escrita extends Thread{
		public void run(){
			while(true){
				solicita_escrita();
				mon.escreve();
			}
		}
		private void solicita_escrita(){
			import java.util.Scanner;

public class ProdutorConsumidor{
	static final int N=10;
	static escrita e = new escrita();
	static leitura l = new leitura();
	static our_monitor mon = new our_monitor();

	public static void main(String args[]){
		e.start();
		l.start();
	}

	static class escrita extends Thread{
		public void run(){
			while(true){
				solicita_escrita();
				mon.escreve();
			}
		}
		private void solicita_escrita(){System.out.println("Solicitando escrita!");}
	}

	static class leitura extends Thread{
		public void run(){
			while(true){
				solicita_leitura();
				mon.le();
			}
		}
		private void solicita_leitura(){System.out.println("Solicitando leitura!");}
	}

	static class our_monitor{
		private int prod[] = new Produtor[N];
		private int count = 0,lo = 0,hi = 0;

		our_monitor{
			preencheProdutos();
		}
		public synchronized void escreve(int val){
			if(count == N)go_to_sleep();
			buffer[hi] = val;
			hi = (hi + 1)%N;
			count = count + 1;
			if(count == 1)notify();
		}
		public synchronized int le(){
		
			if(count == 0)go_to_sleep();
			int val = buffer[lo];
			lo = (lo + 1)%N;
			count = count - 1;
			if(count == N-1)notify();
			return val;
		}
		private void go_to_sleep(){
			try{
				wait();
			}catch(InterruptedException exc){};
		}
		public void preencheProdutos(){
			prod[0].setId(0);	prod[0].setNome("Produto 1");	prod[0].setPreco(1.50);
			prod[1].setId(0);	prod[1].setNome("Produto 1");	prod[1].setPreco(1.50);
			prod[2].setId(0);	prod[2].setNome("Produto 1");	prod[2].setPreco(1.50);
			prod[3].setId(0);	prod[3].setNome("Produto 1");	prod[3].setPreco(1.50);
			prod[4].setId(0);	prod[4].setNome("Produto 1");	prod[4].setPreco(1.50);
			prod[5].setId(0);	prod[5].setNome("Produto 1");	prod[5].setPreco(1.50);
			prod[6].setId(0);	prod[6].setNome("Produto 1");	prod[6].setPreco(1.50);
			prod[7].setId(0);	prod[7].setNome("Produto 1");	prod[7].setPreco(1.50);
			prod[8].setId(0);	prod[8].setNome("Produto 1");	prod[8].setPreco(1.50);
			prod[9].setId(0);	prod[9].setNome("Produto 1");	prod[9].setPreco(1.50);
		}
	}

	static class Produto{
		private int id;
		private String nome;
		private float preco;

		int getId(){
			return id;
		}
		String getNome(){
			return nome;
		}
		float getPreco(){
			return preco;
		}

		void setId(id newId){
			id = newId;
		}
		void setNome(string newNome){
			nome = newNome;
		}
		void setPreco(flaot newPreco){
			preco = newPreco;
		}

	}

}
		}
	}

	static class leitura extends Thread{
		public void run(){
			while(true){
				solicita_leitura();
				mon.le();
			}
		}
		private void solicita_leitura(){System.out.println("Solicitando leitura!");}
	}

	static class our_monitor{
		private int prod[] = new Produtor[N];
		private int count = 0,lo = 0,hi = 0;

		our_monitor{
			preencheProdutos();
		}
		public synchronized void escreve(int val){
			if(count == N)go_to_sleep();
			buffer[hi] = val;
			hi = (hi + 1)%N;
			count = count + 1;
			if(count == 1)notify();
		}
		public synchronized int le(){
		
			if(count == 0)go_to_sleep();
			int val = buffer[lo];
			lo = (lo + 1)%N;
			count = count - 1;
			if(count == N-1)notify();
			return val;
		}
		private void go_to_sleep(){
			try{
				wait();
			}catch(InterruptedException exc){};
		}
		public void preencheProdutos(){
			prod[0].setId(0);	prod[0].setNome("Produto 1");	prod[0].setPreco(1.50);
			prod[1].setId(0);	prod[1].setNome("Produto 1");	prod[1].setPreco(1.50);
			prod[2].setId(0);	prod[2].setNome("Produto 1");	prod[2].setPreco(1.50);
			prod[3].setId(0);	prod[3].setNome("Produto 1");	prod[3].setPreco(1.50);
			prod[4].setId(0);	prod[4].setNome("Produto 1");	prod[4].setPreco(1.50);
			prod[5].setId(0);	prod[5].setNome("Produto 1");	prod[5].setPreco(1.50);
			prod[6].setId(0);	prod[6].setNome("Produto 1");	prod[6].setPreco(1.50);
			prod[7].setId(0);	prod[7].setNome("Produto 1");	prod[7].setPreco(1.50);
			prod[8].setId(0);	prod[8].setNome("Produto 1");	prod[8].setPreco(1.50);
			prod[9].setId(0);	prod[9].setNome("Produto 1");	prod[9].setPreco(1.50);
		}
	}

	static class Produto{
		private int id;
		private String nome;
		private float preco;

		int getId(){
			return id;
		}
		String getNome(){
			return nome;
		}
		float getPreco(){
			return preco;
		}

		void setId(id newId){
			id = newId;
		}
		void setNome(string newNome){
			nome = newNome;
		}
		void setPreco(flaot newPreco){
			preco = newPreco;
		}

	}

}