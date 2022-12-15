
// Re-write of find_HII_bubbles.c for being accessible within the MCMC

int InitInputIonization(struct UserParams *user_params, struct CosmoParams *cosmo_params,
                     struct InputIonization *box) {

    int status;
    Try{ // Try block around whole function.
    // Makes the parameter structs visible to a variety of functions/macros
    // Do each time to avoid Python garbage collection issues
    Broadcast_struct_global_PS(user_params,cosmo_params);
    Broadcast_struct_global_UF(user_params,cosmo_params);

    int i, j, k;

    omp_set_num_threads(user_params->N_THREADS);

#pragma omp parallel private(i,j,k) num_threads(user_params->N_THREADS)
    {
#pragma omp for
        for (i=0; i<user_params->HII_DIM; i++){
            for (j=0; j<user_params->HII_DIM; j++){
                for (k=0; k<user_params->HII_DIM; k++){
                    box->input_ionization[HII_R_INDEX(i,j,k)] = 0.;
                }
            }
        }
    }
    } // End of try
    Catch(status){
        return(status);
    }

    return(0);
}
