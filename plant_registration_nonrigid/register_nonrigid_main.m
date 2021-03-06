addpath( '../file_management/' );
addpath( genpath( '../third_party/CPD2' ) );
addpath( '../plant_registration' );
addpath( '../PointCloudGenerator' );
addpath( '../third_party/icp' );
rms_e_all = [];
R =  [ 0.9101   -0.4080    0.0724 ;
       0.4118    0.8710   -0.2681 ;
       0.0463    0.2738    0.9607 ];
t = [ 63.3043,  234.5963, -46.8392 ];


filename_0 = sprintf( '../../Data/PlantDataPly/plants_converted82-%03d-clean-clear.ply', 0 );
[Elements_0,varargout_0] = plyread(filename_0);
X = [Elements_0.vertex.x';Elements_0.vertex.y';Elements_0.vertex.z']';
%X = X(1:30:end,:);

% second reference scan
q = 6;
filename_1 = sprintf( '../../Data/PlantDataPly/plants_converted82-%03d-clean-clear.ply', q );
[Elements_1,varargout_1] = plyread(filename_1);
X2 = [Elements_1.vertex.x';Elements_1.vertex.y';Elements_1.vertex.z']';
%X2 = X2(1:30:end,:);
for j=1:q
        X2_dash = R*X2' + repmat(t,size(X2,1),1)';
        X2 = X2_dash';
end

min_size = 300;
max_registerable_dist = 15;
opt.viz = 0;
opt.max_it = 100;
opt.outliers = 0.1;
opt.tol = 1e-12;
opt.rot = 0;
opt.normalize = 0;
opt.scale = 0;
opt.fgt = 2;
opt.method='rigid';
[X2r_x,X2r_y,X2r_z,idx_x2r_unreg] = ...
    registerRecursive( X,X2,opt,min_size,max_registerable_dist );

X2_r = [X2r_x,X2r_y,X2r_z];
Y_reg_all = cell(11,1);

%register all of the indices
registration_indices = [1:5,7:11];
for q=registration_indices
    
    
filename_1 = sprintf( '../../Data/PlantDataPly/plants_converted82-%03d-clean-clear.ply', q );
[Elements_1,varargout_1] = plyread(filename_1);
Y = [Elements_1.vertex.x';Elements_1.vertex.y';Elements_1.vertex.z']';

for j=1:q
        Y_dash = R*Y' + repmat(t,size(Y,1),1)';
        Y = Y_dash';
end
%Y = Y(1:30:end,:);    
[Yr_x,Yr_y,Yr_z,Yr_unreg] = ...
    registerRecursive( X,Y,opt,min_size,max_registerable_dist );

[Yr_x2,Yr_y2,Yr_z2,Yr_unreg2] = ...
    registerRecursive( X2,Yr_unreg,opt,min_size,max_registerable_dist);          
%[neighbour_id] = kNearestNeighbors(X, Yr_subdiv, 1 );
% get nearest neighbour for each point in the original cloud in the
% matched cloud
%Yr_subdiv = [Yr_x,Yr_y,Yr_z];
%filename = sprintf( '../../Data/Yr_subdiv%02d-%s.mat',[q datestr(now,'dd.mm.yy.HH.MM') ] )
%save(filename,'Yr_subdiv');
%{
neighbour_id_unique = unique(neighbour_id);
Y_reg_all{q} = Yr_subdiv;
Yr_subdiv = [];
X_reg = ones(size(X(neighbour_id_unique,:)));
[X_reg(:,1),X_reg(:,2),X_reg(:,3)] = registerRecursive( ...
                                          Y,X(neighbour_id_unique,:),...
                                          opt, min_size );

neighbour_id=[];
neighbour_dist=[];
[neighbour_id_reg,neighbour_dist_reg] = ...
                    kNearestNeighbors( X,X_reg,1);%X_reg, X, 1 );
sprintf('RMS-E: ' )
rms_e = sqrt( sum(neighbour_dist_reg(:)) / length(neighbour_dist_reg(:)) )
rms_e_all = [rms_e_all rms_e];
neighbour_id_reg=[];
neighbour_dist_reg=[];
%}
Y_reg_all{q} = [Yr_x' Yr_x2' ; Yr_y' Yr_y2' ; Yr_z' Yr_z2']';
%Y_reg_all{q} = [Yr_x' Yr_x2' ; Yr_y' Yr_y2' ; Yr_z' Yr_z2']; %Yr_subdiv;
filename = sprintf( '../../Data/Yq%02d-%s.mat',[q datestr(now,'dd.mm.yy.HH.MM') ] )
Yq = Y_reg_all{q};
save(filename,'Yq');
Yq = [];
end