
void fallbackSimpleSort(int *fmap,int *eclass,int lo,int hi)
{
  if (lo == hi) 
    return ;
  if (hi - lo > 3) {
    for (int i = hi - 4; i >= lo; i--) {
      int j;
      int tmp = fmap[i];
      unsigned int ec_tmp = (unsigned int )eclass[tmp];
      for (j = i + 4; j <= hi && ec_tmp > eclass[fmap[j]]; j += 4) 
        fmap[j - 4] = fmap[j];
      fmap[j - 4] = tmp;
    }
  }
  for (int i = hi - 1; i >= lo; i--) {
    int j;
    int tmp = fmap[i];
    unsigned int ec_tmp = (unsigned int )eclass[tmp];
    for (j = i + 1; j <= hi && ec_tmp > eclass[fmap[j]]; j++) 
      fmap[j - 1] = fmap[j];
    fmap[j - 1] = tmp;
  }
}
