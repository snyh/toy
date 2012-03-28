#encoding:utf-8
class MainController < ApplicationController
  def index
    @events = Event.order("date").limit(10)
    @classes = Classbj.all()
    @departments = Department.all().sort {|a,b| a.avg_score <=> b.avg_score}

    @chart_department = self.chart1
    @chart_avg = self.chart2

  end

  protected
  def chart1
    data = @departments.map {|x| [x.name, x.score]}
    LazyHighCharts::HighChart.new('pie') do |f|
      f.title({:text => "院校累计分数贡献榜"})
      f.series(:type=>'pie', :name=>'累计贡献', :data=>data)
    end
  end
  def chart2
    d1,d2 = [[],[]]
    @departments.each {|x| d1.push x.name; d2.push x.avg_score}
    LazyHighCharts::HighChart.new('graph') do |f|
      f.title({:text => "院校人均分数排行"})
      f.options[:chart][:defaultSeriesType] = "column"
      f.options[:legend][:enabled] = false
      f.options[:xAxis][:categories] = d1
      f.series(:name=>'平均分', :data=>d2)
    end
  end
end
