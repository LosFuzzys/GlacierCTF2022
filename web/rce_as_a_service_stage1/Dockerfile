FROM mcr.microsoft.com/dotnet/aspnet:6.0 AS base
WORKDIR /app
EXPOSE 8080

FROM mcr.microsoft.com/dotnet/sdk:6.0 AS build
WORKDIR /src
COPY ["RCEaaS.csproj", "./"]
RUN dotnet restore "RCEaaS.csproj"
COPY . .
WORKDIR "/src/"
RUN dotnet build "RCEaaS.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "RCEaaS.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
COPY ./flag.txt /

# Create a low-privileged user that can only *read* the flag,
# Why? Because of:
#    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣠⣤⣤⣤⠴⠶⠶⠶⠶⠒⠾⠿⠿⠿⣛⡛⠛⠛⠛⠛⠛⠻⠿⡷⠶⠶⢶⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
#    ⠀⠀⠀⠀⠀⠀⢀⣤⡾⠟⠛⠉⣉⣩⣤⡴⠦⠭⠥⠒⠒⠒⠒⠒⠒⠒⠒⠂⠤⠀⢀⣀⠈⠑⠢⢀⠑⠀⠀⠙⢿⣄⠀⠀⠀⠀⠀⠀⠀⠀
#    ⠀⠀⠀⠀⣠⡾⠟⠁⣠⡢⠔⢫⠞⣉⣀⡀⠀⠀⠀⠐⠒⠄⠠⠀⠀⠐⡠⢂⡴⠶⠦⢴⡊⠙⠒⠀⠑⠀⠀⠀⠀⠹⣧⡀⠀⠀⠀⠀⠀⠀
#    ⠀⠀⠀⢠⣿⠀⡠⢊⡫⡀⢀⣤⣞⣡⣼⣿⣦⠀⠐⠉⠱⡤⢢⠦⠀⠀⣰⠋⣀⣤⣴⣿⣿⣆⠀⠀⠀⠀⠀⠀⠙⠳⢾⣷⡀⠀⠀⠀⠀⠀
#    ⠀⠀⠀⣼⡏⣰⠁⠠⠪⠿⣟⠩⠉⠀⠀⠈⢻⡧⠄⣴⠞⠁⣣⠖⠀⢰⣧⠞⠁⠀⠠⠍⡻⣼⡆⠀⢀⣀⡀⠀⠀⠀⠀⠙⣧⡀⠀⠀⠀⠀
#    ⠀⣴⡾⠟⣽⢋⡒⠦⡢⠐⠀⠄⠒⠲⠶⠖⠋⠀⢸⡇⠀⠀⠙⠀⠀⠘⣷⡀⠤⠤⠀⠀⠀⠉⠛⠻⡍⠀⠐⠉⣉⣗⠦⣄⠘⢿⣦⡀⠀⠀
#    ⣾⠋⠀⢸⠇⢹⠟⢦⣄⡀⠄⠀⠀⠉⠁⣰⠶⢖⣾⠁⠀⠀⠀⠐⠒⢦⣤⣝⠓⠒⠒⠊⠀⠈⠀⠀⢀⣴⠞⠋⣽⢻⠱⡈⢳⡈⢯⠻⣦⠀
#    ⣿⠀⡆⠸⣆⢸⡦⡄⠉⠛⠶⣬⣔⡀⠘⠁⢸⡏⠁⠀⠀⠶⢦⣤⡀⠈⡇⠈⠳⠄⠀⢀⠀⠀⣀⡴⢿⠥⣄⣼⠃⡌⠀⢳⠀⢳⠸⡄⠘⣧
#    ⣿⡀⡇⠀⠈⠷⣇⡗⣦⣠⡀⠈⠙⠛⡿⠶⠾⢿⣶⣶⣶⣶⣀⣀⣁⣀⣁⣀⣠⣤⣿⠿⠟⠛⣉⣀⡏⢀⡿⠁⠰⠀⠀⢸⠀⠀⠀⡇⠀⣿
#    ⠘⣷⡁⢀⢸⠀⣿⠀⡟⠀⣷⠋⢳⡾⠙⢷⡀⠀⣠⠤⣌⠉⠉⣉⣭⣍⠉⣩⠭⢤⣀⡴⠚⢲⡇⠀⣿⠏⠀⠠⠃⠀⠀⣸⠀⠀⠀⠁⣼⠏
#    ⠀⠘⣷⢸⠈⡆⣿⣿⣁⢀⠏⠀⢸⡇⠀⠀⢻⣾⠁⠀⠈⢳⣴⠏⠀⠹⣶⠇⠀⠀⢹⡀⣀⣼⣷⡾⠃⢠⠀⢀⠄⠀⠠⠁⠀⠀⣀⣼⠋⠀
#    ⠀⠀⢸⣿⠀⡇⣿⣿⣿⣿⣤⣄⣼⠃⠀⠀⢸⡟⠀⠀⠀⠀⣿⠀⠀⠀⣿⡀⠀⢀⣿⣿⣿⣿⡟⠁⢠⠃⠀⠀⠀⡀⠀⠀⢀⣼⠟⠁⠀⠀
#    ⠀⠀⢸⣿⠀⡇⣿⣿⣿⣿⣿⣿⣿⣷⣶⣦⣿⣧⣀⣀⣤⣤⣿⣶⣶⣶⣿⣿⣿⣿⣿⣿⡿⣫⠄⢀⠂⠀⠀⠀⠀⡄⠀⢠⣿⠁⠀⠀⠀⠀
#    ⠀⠀⢸⣿⠀⣧⣿⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣩⠞⠁⡰⠁⠀⠠⠀⠀⡐⠀⢠⡾⠃⠀⠀⠀⠀⠀
#    ⠀⠀⢸⡇⠀⣿⡟⢀⡟⠀⣿⠋⢻⡿⠻⣿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢁⡔⠁⠠⠞⠀⠀⠀⠁⢀⠌⢀⣴⠟⠁⠀⠀⠀⠀⠀⠀
#    ⠀⠀⣼⠃⡄⢹⣿⡙⢇⣠⡇⠀⣸⠁⢠⠇⠀⢹⠃⢠⠛⠙⡏⠉⣇⣼⠿⢃⡴⠋⠀⠐⠁⠔⠀⠐⠁⣠⣢⣴⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀
#    ⠀⠀⣿⠀⡇⠸⡿⢷⣄⡀⠙⠒⠳⡤⠼⣄⣀⢼⣀⢾⣀⣸⣶⡾⠟⣁⡴⠋⢀⡠⠒⠁⠀⠀⢀⣤⡾⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
#    ⠀⠀⣿⠀⠻⡄⠉⠠⡉⠙⠳⠶⣶⣶⣶⣾⣷⣶⠿⠿⠟⠋⠉⠖⠫⠕⠒⠈⠀⢀⣤⣴⡶⠟⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
#    ⠀⠀⢿⡄⠀⠉⠓⠀⠀⠈⠉⠠⠌⠀⠀⠀⣀⠠⠄⠂⠠⠤⠤⠴⠊⠁⣀⣴⡾⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
#    ⠀⠀⠈⠻⣦⣑⠒⠤⣅⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣶⠶⠶⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
#    ⠀⠀⠀⠀⠈⠙⠛⠶⠶⣤⣭⣭⣭⣭⣴⠶⠶⠛⠛⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

RUN useradd el_fuzzo
USER el_fuzzo

# We specify a non-privileged port so that the application
# can run under our newly created user account.
ENV ASPNETCORE_URLS=http://*:8080

ENTRYPOINT ["dotnet", "RCEaaS.dll"]
