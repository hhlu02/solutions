int N, Q;
int A[1d5];
ll tot;

fenwick<ll> fw;

{
  rd(N, Q);
  rd(A(N));

  fw.walloc(N);
  fw.init(N);
  rep(i,N) fw.add(i, A[i]), tot += A[i];

  while(Q--){
    char @op;

    if(op == '!'){
      int @X;
      ll @V;
      --X;
      ll d = V - A[X];
      A[X] = V;
      tot += d;
      fw.add(X,d);
    }
    else{
      int @K;
      int i = bsearch_max[int,i,0,N-K](fw.get(i-1) + fw.get(i+K-1) <= tot);
      ll x = fw.get(i-1);
      ll y = fw.get(i+K-1);
      ll ans = K == 1 ? tot - x - y : tot - 2 * x;
      if(i < N-K) ans <?= K == 1 ? 2 * y + A[i+1] - tot : 2 * (y + A[i+K]) - tot;
      wt(ans);
    }
  }
}
