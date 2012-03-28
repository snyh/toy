class CreateEvents < ActiveRecord::Migration
  def change
    create_table :events do |t|
      t.references :student
      t.references :regulation
      t.date :date
      t.string :remark

      t.timestamps
    end
  end
end
