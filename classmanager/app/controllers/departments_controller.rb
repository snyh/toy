class DepartmentsController < ApplicationController
  def show
    d = Department.find(params[:id])
    @departname = d.name
    @classes = d.classes.sort {|a,b| a.rank_department <=> b.rank_department}
  end
end
